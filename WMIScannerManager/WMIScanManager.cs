using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
using System.Management;
using System.Collections.Specialized;
using System.Configuration;
using Microsoft.Win32;
using System.IO;

namespace WMIScannerManager
{
    public enum DeviceClass
    {
        Scanner,
        Cradle
    }

    public enum PushActivity
    {
        Configuration,
        Firmware
    }

    public class WMIScanManager
    {
        #region Declarations

        private StringCollection partCollection = new StringCollection();
        private StringCollection serialCollection = new StringCollection();

        private string strScanCount = "0";
        private string strPartNumber = "";
        private string strSerialNumber = "";
        private string strComputer;

        private bool firmwareInjectionCompleted = false;
        private bool firmwareInProgress = false;
        private bool firmwareUpdateError = false;

        private int no_of_Scanners = 0;

        private ManagementScope mgmtScope;
        private ManagementObjectSearcher objSearcher = null;
        private ManagementEventWatcher discEvWatcher;
        static private ManagementEventWatcher fwupEvWatcher;

        private DeviceClass currentDeviceClass;
        private bool logEnabled = false;

        ManagementObject o;

        #endregion

        public WMIScanManager()
        {
            ConnectionOptions options = new ConnectionOptions();
            options.Authentication = AuthenticationLevel.Packet;
            options.Impersonation = ImpersonationLevel.Impersonate;
            options.EnablePrivileges = true;

            mgmtScope = new ManagementScope("\\\\localhost\\root\\CIMV2", options);

            try
            {
                mgmtScope.Connect();

                EventQuery query = new EventQuery("SELECT * FROM SymbScnrDiscoveryEvent");
                discEvWatcher = new ManagementEventWatcher(mgmtScope, query);
                discEvWatcher.EventArrived += new EventArrivedEventHandler(EventArrived);
                discEvWatcher.Start();

                query = new EventQuery("SELECT * FROM SymbScnrFirmwareUpdateEvent");
                fwupEvWatcher = new ManagementEventWatcher(mgmtScope, query);
                fwupEvWatcher.EventArrived += new EventArrivedEventHandler(this.UpdateFirmwareEventArrived);
                
                try
                {
                    discEvWatcher.Start();
                    fwupEvWatcher.Start();
                }
                catch (Exception)
                {
                    string errmsg = "Failed to Subscribe for Events\r\n\r\nPossible Reasons:\r\n"
                    + "- Currently logged-on user credentials may not be sufficient\r\n"
                    + "- Firewall group policies of remote host may not be configured";
                    LogMessage(errmsg);
                }

                Discover();
                InitializeWMI();
            }
            catch (Exception)
            {
                return;
            }
            
            o = new ManagementObject();
            o.Scope = mgmtScope;
            o.Path = new ManagementPath("Symbol_BarcodeScanner.PartNumber='" + strPartNumber + "',SerialNumber='" + strSerialNumber + "'");
        }

        public void getInfo() {
            LogMessage("PartNumber: " + strPartNumber);
            LogMessage("SerialNumber: " + strSerialNumber);
            LogMessage("DateOfManufacture: " + DOM);
            LogMessage("FirmwareVersion: " + FWV);        
        }

        public bool LogEnabled
        {
            get
            {
                return logEnabled;
            }
            set 
            {
                logEnabled = value;
            }
        }

        public void EventArrived(object sender, EventArrivedEventArgs e)
        {
            if (firmwareInProgress)
            {
                LogMessage("Error: discovery event while a firmware upgrade is in progress ... exiting");
                firmwareUpdateError = true;
                return;
            }
            string serial = e.NewEvent["SerialNumber"].ToString();
            string model = e.NewEvent["PartNumber"].ToString();

            ////nov 2012
            //LogMessage("Logging PropertyData");
            //foreach (PropertyData pd in e.NewEvent.Properties)
            //    LogMessage("EventArrived PropertyData: "+pd.Name);

            //LogMessage("Logging QualifierData");
            //foreach (QualifierData qd in e.NewEvent.Qualifiers)
            //    LogMessage("EventArrived QualifierData: " + qd.Name);

            Discover();
            //InitializeWMI();
        }

        string DOM = "";
        string FWV = "";
        string HEALTH = "";//2013
        private void InitializeWMI()
        {
            if (partCollection.Count == 1)
            {
                strPartNumber = partCollection[0].Trim();
                strSerialNumber = serialCollection[0].Trim();
                //strLastModel = partCollection[0].Substring(0, cmbModel.Text.Length)
            }
            else
            {
                for (int i = 0; i < partCollection.Count; i++)
                { 
                    if (partCollection[i].Trim().StartsWith("STB"))
                    {      
                        strPartNumber = partCollection[i].Trim();
                    
                        strSerialNumber = serialCollection[i].Trim();
                    }
                }
            }
            


            try
            {
                ManagementObject o = new ManagementObject();
                o.Scope = mgmtScope;
                o.Path = new ManagementPath("Symbol_BarcodeScanner.PartNumber='" +
                   strPartNumber + "',SerialNumber='" + strSerialNumber + "'");

                //// Check if the SerialNumber is equalant (Used to create an exception if the WMI Path is invalid)
                // The exception is handled below
                if (o["SerialNumber"].ToString() == strSerialNumber)
                {
                    strScanCount = o["TotalDecodes"].ToString();
                    LogMessage("SerialNumber: " + strSerialNumber);

                    // Get the Manufacture Date and Firmware Version	
                    Object objVal = o.GetPropertyValue("DateOfManufacture");
                    if (objVal != null)
                    {
                        DOM = objVal.ToString();
                        LogMessage("DateOfManufacture: " + DOM);
                    }
                    objVal = o.GetPropertyValue("FirmwareVersion");
                    if (objVal != null)
                    {
                        FWV = objVal.ToString();
                        LogMessage("FirmwareVersion: " + FWV);

                    }

                    objVal = o.GetPropertyValue("scanner health");
                    if (objVal != null)
                    {
                        HEALTH = objVal.ToString();
                        LogMessage("scanner health: " + HEALTH);

                    }

                    objVal = o.GetPropertyValue("FirmwareUpdateStatus");
                    if (objVal != null)
                    {
                        string fwupStatus = objVal.ToString();
                        //if (fwupStatus.Contains("Progress"))
                        //{
                        //    objVal = o.GetPropertyValue("FirmwareUpdateBlockCount");
                        //    string blocks = objVal.ToString();
                        //    //txtFirmwareProgress.Text = "Progress - Block:" + blocks;
                        //    UpdateFirmwareDownloadProgress("Progress - Block:" + blocks);
                        //}
                        //else
                        //{
                        //    //txtFirmwareProgress.Text = fwupStatus;
                        //    UpdateFirmwareDownloadProgress(fwupStatus);
                        //}
                    }
                }
            }
            // Generic Exception Handler
            catch (Exception)
            {
                // Exception could occur if a scanner is disconnected while
                // executing this function.
                // Re-discover scanners
                Discover();
            }
        }

        private void Discover()
        {
            lock (this)
            {
                try
                {
                    objSearcher = new ManagementObjectSearcher(mgmtScope,
                        new WqlObjectQuery("SELECT * FROM Symbol_BarcodeScanner"));

                    // Enumurate the ManagementObjectSearcher and populate the PartNumber 
                    //(Hidden) and Serial Number (Hidden) List Boxes
                    foreach (ManagementObject mo in objSearcher.Get())
                    {
                        no_of_Scanners++;
                        // Extract Model number from the Partnumber
                        string tempModel = mo["PartNumber"].ToString();
                        if (tempModel.IndexOf("-") > 0)
                        {
                            tempModel = tempModel.Substring(0, tempModel.IndexOf("-"));
                        }
                        partCollection.Add(mo["PartNumber"].ToString());

                        serialCollection.Add(mo["SerialNumber"].ToString());

                    }
                    if (no_of_Scanners > 0)
                    {
                        strComputer = "localhost";
                    }
                    else
                    {
                        strComputer = ".";
                    }

                    
                }
                // Generic All Exception Handler
                catch (Exception e)
                {
                    LogMessage("Error during the Discovery phase: " + e.Message + "\nStackTrace: " + e.StackTrace);
                }
            }

        }

        public void SetTargetDevice(DeviceClass dclass)
        {
            currentDeviceClass = dclass;
            string startStringPartNo;

            if (partCollection.Count == 1)
            {
                LogMessage("SetTargetDevice: found just one device");
                strPartNumber = partCollection[0].Trim();
                strSerialNumber = serialCollection[0].Trim();
            }
            else
            {
                LogMessage("SetTargetDevice: found two devices");
                if (dclass == DeviceClass.Scanner)
                {
                    LogMessage("SetTargetDevice: setting scanner mode");
                    startStringPartNo = "DS";
                }
                else
                {
                    LogMessage("SetTargetDevice: setting cradle mode");
                    startStringPartNo = "STB";
                }

                for (int i = 0; i < partCollection.Count; i++)
                {
                    if (partCollection[i].Trim().StartsWith(startStringPartNo))
                    {
                        strPartNumber = partCollection[i].Trim();
                        strSerialNumber = serialCollection[i].Trim();
                    }
                }
            }
        }

        public void PushConfigurationFromFile(string filePath)
        {
            LogMessage("PushConfigurationFromFile: configuration from " + filePath);
            string configurationString = string.Empty;
            if (File.Exists(filePath))
            {
                StreamReader sr = new StreamReader(filePath);
                configurationString += sr.ReadToEnd();
                sr.Close();
            }
            else
                LogMessage("PushConfigurationFromFile: file not found");
            
            if (configurationString.Length != 0)
            {
                LogMessage("PushConfigurationFromFile: configuration is:\n"+configurationString);
                pushConfiguration(configurationString);
            }
            else
                LogMessage("PushConfigurationFromFile: file empty");

        }

        private void pushConfiguration(string configuration)
        {
            string strWizPartNumber = strPartNumber;
            string strWizSerialNumber = strSerialNumber;
            try
            {
                LogMessage("PartNumber: " + strPartNumber);
                LogMessage("SerialNumber: " + strSerialNumber);
                LogMessage("DateOfManufacture: " + DOM);
                LogMessage("FirmwareVersion: " + FWV);

                LogMessage("pushConfiguration: " + "Start Cloning: " + strWizSerialNumber );
                ManagementObject o = new ManagementObject();
                o.Scope = mgmtScope;
                o.Path = new ManagementPath("Symbol_BarcodeScanner.PartNumber='" + strWizPartNumber + "',SerialNumber='" + strWizSerialNumber + "'");

                // Create ManagementBaseObject and get the parameters to the Method "StoreAttributes"
                ManagementBaseObject inParams = o.GetMethodParameters("StoreAttributes");

                // Populate the parameter "attributeSettings" with the content of the clipboard
                inParams["attributeSettings"] = configuration; //Clipboard.GetDataObject().ToString(); // (string)Clipboard.GetDataObject().GetData(DataFormats.Text).ToString();

                // Invoke the method "StoreAttributes" and retrieve the Result
                ManagementBaseObject outparams = o.InvokeMethod("StoreAttributes", inParams, null);

                // Update Management Textbox				
                LogMessage("pushConfiguration: " + "Cloning Done: " + strWizSerialNumber);
                string strRet = outparams["ReturnValue"].ToString();
                LogMessage("pushConfiguration: " + "Return Value: " + (strRet.Equals("0") ? "Succeeded" : "Failed"));
            }
            // ManagementException Exception Handler
            // Invoked if the Scanner is not connected to the system at the time command is executed.
            catch (ManagementException err)
            {
                LogMessage("pushConfiguration: Error: " + err.Message.ToString() + "\nCheck if the Scanner is still connected.");
            }
            // Generic Exception Handler
            catch (Exception err)
            {
                LogMessage("pushConfiguration: Unknown Error: " + err.Message.ToString());
            }
        }

        public void LogMessage(string message)
        {
            if (logEnabled)
            {
                try
                {
                    if (!File.Exists("Log.txt"))
                    {
                        FileStream fs = File.Create("Log.txt");
                        fs.Close();
                    }
                    StreamWriter writer;
                    writer = File.AppendText("Log.txt");
                    writer.WriteLine(DateTime.Now.ToString() + "\t-\t" + message);
                    writer.Close();
                }
                catch { }
            }
        }

        internal void PushFirmwareFromFile(string filePath)
        {
            LogMessage("PushFirmwareFromFile: firmware from " + filePath);
            string configurationString = string.Empty;
            if (File.Exists(filePath))
            {
                if(!injectNewFirmware(filePath))
                    return;
                firmwareInProgress = true;
                while (!firmwareInjectionCompleted && !firmwareUpdateError)
                    Thread.Sleep(1000);
                if (firmwareUpdateError)
                    return;
                startNewFirmware();
            }
            else
                LogMessage("PushFirmwareFromFile: file not found");
        }

        private bool injectNewFirmware(string fwPath)
        {
            string strWizPartNumber = strPartNumber;
            string strWizSerialNumber = strSerialNumber;
            try
            {
                LogMessage("injectNewFirmware: " + "Start Injecting: " + strWizSerialNumber);
                ManagementObject o = new ManagementObject();
                o.Scope = mgmtScope;
                o.Path = new ManagementPath("Symbol_BarcodeScanner.PartNumber='" + strWizPartNumber + "',SerialNumber='" + strWizSerialNumber + "'");

                // Create ManagementBaseObject and get the parameters to the Method "StoreAttributes"
                ManagementBaseObject inParams = o.GetMethodParameters("UpdateFirmware");

                // Populate the parameter "attributeSettings" with the content of the clipboard
                inParams["filePath"] = fwPath; //Clipboard.GetDataObject().ToString(); // (string)Clipboard.GetDataObject().GetData(DataFormats.Text).ToString();

                // Invoke the method "StoreAttributes" and retrieve the Result
                ManagementBaseObject outparams = o.InvokeMethod("UpdateFirmware", inParams, null);

                // Update Management Textbox				
                LogMessage("injectNewFirmware: " + "Injecting Done: " + strWizSerialNumber);
                string strRet = outparams["ReturnValue"].ToString();
                LogMessage("injectNewFirmware: " + "Return Value: " + (strRet.Equals("0") ? "Completed" : "Failed -" + strRet));
            }
            // ManagementException Exception Handler
            // Invoked if the Scanner is not connected to the system at the time command is executed.
            catch (ManagementException err)
            {
                LogMessage("injectNewFirmware: Error: " + err.Message.ToString() + "\nCheck if the Scanner is still connected.");
                return false;
            }
            // Generic Exception Handler
            catch (Exception err)
            {
                LogMessage("injectNewFirmware: Unknown Error: " + err.Message.ToString());
                return false;
            }
            return true;
        }

        private void startNewFirmware()
        {
            //StartNewFirmware
            string strWizPartNumber = strPartNumber;
            string strWizSerialNumber = strSerialNumber;
            try
            {
                LogMessage("startNewFirmware: " + "Starting: " + strWizSerialNumber);
                ManagementObject o = new ManagementObject();
                o.Scope = mgmtScope;
                o.Path = new ManagementPath("Symbol_BarcodeScanner.PartNumber='" + strWizPartNumber + "',SerialNumber='" + strWizSerialNumber + "'");

                // Create ManagementBaseObject and get the parameters to the Method "StoreAttributes"
                ManagementBaseObject inParams = o.GetMethodParameters("StartNewFirmware");
                ManagementBaseObject outparams = o.InvokeMethod("StartNewFirmware", inParams, null);

                // Update Management Textbox				
                LogMessage("startNewFirmware: " + "Start Done: " + strWizSerialNumber);
                string strRet = outparams["ReturnValue"].ToString();
                LogMessage("startNewFirmware: " + "Return Value: " + (strRet.Equals("0") ? "Completed" : "Failed"));
            }
            // ManagementException Exception Handler
            // Invoked if the Scanner is not connected to the system at the time command is executed.
            catch (ManagementException err)
            {
                LogMessage("startNewFirmware: Error: " + err.Message.ToString() + "\nCheck if the Scanner is still connected.");
            }
            // Generic Exception Handler
            catch (Exception err)
            {
                LogMessage("startNewFirmware: Unknown Error: " + err.Message.ToString());
            }

        }
        
        public void UpdateFirmwareEventArrived(object sender, EventArrivedEventArgs e)
        {
            string serial = e.NewEvent["SerialNumber"].ToString();
            string model = e.NewEvent["PartNumber"].ToString();
            if (serial.Equals(strSerialNumber) && model.Equals(strPartNumber))
            {
                string type = e.NewEvent["Type"].ToString();
                string status = "";
                if (type.Equals("1"))
                {
                    status = "Session Started";
                }
                else if (type.Equals("2"))
                {
                    status = "Download Started";
                }
                else if (type.Equals("3"))
                {
                    string blockCount = e.NewEvent["Progress"].ToString();
                    status = "Progress - Block:" + blockCount;
                }
                else if (type.Equals("12"))
                {
                    status = "Download Ended";
                }
                else if (type.Equals("11"))
                {
                    status = "Session Ended";
                    firmwareInjectionCompleted = true;
                }
                LogMessage("FirmwareUpdateStatus: " + status);
            }
        }
    }
}
