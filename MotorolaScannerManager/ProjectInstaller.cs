using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration.Install;
using Microsoft.Win32;
using System.Management;
using System.IO;
using System.Reflection;


namespace MotorolaScannerManager
{
    [RunInstaller(true)]
    public partial class ProjectInstaller : Installer
    {
        public ProjectInstaller()
        {
            InitializeComponent();


            try
            {
                ConnectionOptions coOptions = new ConnectionOptions();
                coOptions.Impersonation = ImpersonationLevel.Impersonate;
                ManagementScope mgmtScope = new ManagementScope(@"root\CIMV2", coOptions);
                mgmtScope.Connect();
                ManagementObject wmiService;
                wmiService = new ManagementObject("Win32_Service.Name='" + "MotorolaScannerManagerService" + "'");
                ManagementBaseObject InParam = wmiService.GetMethodParameters("Change");
                InParam["DesktopInteract"] = true;
                wmiService.InvokeMethod("Change", InParam, null);
            }
            catch (Exception ex)
            {
                try
                {
                    if (!File.Exists("MotorolaScannerManagerInstallerErrorLog.txt"))
                    {
                        FileStream fs = File.Create("MotorolaScannerManagerInstallerErrorLog.txt");
                        fs.Close();
                    }
                    StreamWriter writer;
                    writer = File.AppendText("MotorolaScannerManagerInstallerErrorLog.txt");
                    writer.WriteLine(DateTime.Now.ToLongTimeString() + "\tError Installing Motorola Scanner Manager" + ex.Message);
                    writer.WriteLine(DateTime.Now.ToLongTimeString() + "\tError Installing Motorola Scanner Manager" + ex.StackTrace);
                    writer.Close();
                }
                catch { }
            }

            this.Committed +=new InstallEventHandler(ProjectInstaller_Committed);

            

        }

        void ProjectInstaller_Committed(object sender, InstallEventArgs e)
        {
            try
            {
                string installationPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);

                RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\MotorolaScannerManager", true);
                if (key == null)
                {
                    key = Registry.LocalMachine.CreateSubKey(@"SOFTWARE\MotorolaScannerManager", RegistryKeyPermissionCheck.ReadWriteSubTree);
                }
                key.SetValue("ConfigurationFilePath", installationPath);
                key.Close();
            }
            catch(Exception ex)
            {
                try
                {
                    if (!File.Exists("MotorolaScannerManagerInstallerErrorLog.txt"))
                    {
                        FileStream fs = File.Create("MotorolaScannerManagerInstallerErrorLog.txt");
                        fs.Close();
                    }
                    StreamWriter writer;
                    writer = File.AppendText("MotorolaScannerManagerInstallerErrorLog.txt");
                    writer.WriteLine(DateTime.Now.ToLongTimeString() + "\tError Installing Motorola Scanner Manager" + ex.Message);
                    writer.WriteLine(DateTime.Now.ToLongTimeString() + "\tError Installing Motorola Scanner Manager" + ex.StackTrace);
                    writer.Close();
                }
                catch { }
            }
        }
    }
}
