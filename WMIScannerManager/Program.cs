using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;
using Microsoft.Win32;

//NDZL 23/SET/2019: BUILT ON WIN10 VS2017 => funziona! info:true log:true
//PUSH:CONFIGURATION e PUSH:FIRMWARE da testare

namespace WMIScannerManager
{
    class Program
    {
        [DllImport("user32.dll")]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        static PushActivity Push;
        static string Path;
        static DeviceClass Device;
        static bool Log = false;
        static bool NoUI = false;
        static bool getInfo = false;

        static void Main(string[] args)
        {

            if (args.Length < 0)
            {
                Console.WriteLine("Argument format not correct, please use:");
                Console.WriteLine("\tinfo:true: should get part and serial no. of the device, date of manuf.");
                Console.WriteLine("\tTYPE: configuration or firmware");
                Console.WriteLine("\tPATH: firmware or configuration file path between \"");
                Console.WriteLine("\tDEVICE: cradle or scanner");
                Console.WriteLine("\tLOG: true or false");
                Console.WriteLine("\tNOUI: true or false");
                Console.ReadLine();
                return;
            }
            foreach (string argument in args)
            {
                bool result = ProcessArgument(argument.ToLower());
                if (!result)
                {
                    Console.WriteLine("Argument format not correct, please use:");
                    Console.WriteLine("\tINFO: to get part and serial no. of the device, date of manuf.");
                    Console.WriteLine("\tTYPE: configuration or firmware");
                    Console.WriteLine("\tPATH: firmware or configuration file path between \"");
                    Console.WriteLine("\tDEVICE: cradle or scanner");
                    Console.WriteLine("\tLOG: true or false");
                    Console.WriteLine("\tNOUI: true or false");
                    Console.ReadLine();
                    return;
                }
            }

            if (NoUI)
            {
                Console.Title = "MotManager";
                IntPtr hWnd = FindWindow(null, "MotManager");
                if (hWnd != IntPtr.Zero)
                    ShowWindow(hWnd, 0);
            }

            WMIScanManager wmiManager = new WMIScanManager();
            wmiManager.LogEnabled = Log;
            wmiManager.SetTargetDevice(Device);

            if (getInfo)
                wmiManager.getInfo();
            else
            {

                if (Push == PushActivity.Configuration)
                    wmiManager.PushConfigurationFromFile(Path);

                if (Push == PushActivity.Firmware)
                    wmiManager.PushFirmwareFromFile(Path);
            }


        }

        private static bool ProcessArgument(string argument)
        {
            string command = argument.Substring(0, argument.IndexOf(":"));
            string parameter = argument.Substring(argument.IndexOf(":") + 1, argument.Length - argument.IndexOf(":") -1);
            bool returnvalue = true;

            switch (command)
            {
                case("info"):
                    getInfo = true;
                    returnvalue = true;
                    break;
                case("type"):
                    if (parameter == "configuration")
                        Push = PushActivity.Configuration;
                    else
                        if (parameter == "firmware")
                            Push = PushActivity.Firmware;
                        else
                            return false;
                    break;
                case ("path"):
                    Path = parameter;
                    break;
                case ("device"):
                    if (parameter == "cradle")
                        Device = DeviceClass.Cradle;
                    else
                        if (parameter == "scanner")
                            Device = DeviceClass.Scanner;
                        else 
                            return false;
                    break;
                case ("log"):
                    returnvalue = Boolean.TryParse(parameter, out Log);
                    break;
                case ("noui"):
                    returnvalue = Boolean.TryParse(parameter, out NoUI);
                    break;
                default:
                    break;
            }
            return returnvalue;
        }

    }
}
