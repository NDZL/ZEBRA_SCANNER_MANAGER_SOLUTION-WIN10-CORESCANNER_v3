using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.ServiceProcess;
using System.Text;
using System.Configuration;
using System.Threading;
using System.IO;
using Microsoft.Win32;
using System.Runtime.InteropServices;
using System.Security.Principal;



namespace MotorolaScannerManager
{
    public partial class ScannerManagerService : ServiceBase
    {
        private string scannerManagerExecutable;
        private int managementInterval = 1000;
        private bool logEnabled = false;
        private int RegistryScanDataInterval = 100;
        private int lastScanTime = 0;

        public ScannerManagerService()
        {
            InitializeComponent();
            this.EventLog.Log = "Application";

            scannerManagerExecutable = ConfigurationSettings.AppSettings["ScannerManagerExecutable"];
            managementInterval = Int32.Parse(ConfigurationSettings.AppSettings["ManagementInterval"]);
            RegistryScanDataInterval = Int32.Parse(ConfigurationSettings.AppSettings["RegistryScanDataInterval"]);
            logEnabled = Boolean.Parse(ConfigurationSettings.AppSettings["LogEnabled"]);
        }

        private void LogMessage(string message)
        {
            if(logEnabled)
                this.EventLog.WriteEntry(message, EventLogEntryType.Information);
        }

        protected override void  OnStart(string[] args)
        {
            LogMessage("Motorola Scanner Manager Service: OnStart-1");

            try
            {
                scannerManagerExecutable = System.AppDomain.CurrentDomain.BaseDirectory + "\\" + scannerManagerExecutable;

                ////ORIGINAL START APP
                //StartScanManagerApplication();   //rem nov2012
                //LogMessage("Motorola Scanner Manager Service: process(" + scannerManagerExecutable + ") started. OnStart-2");

                timerManager.Elapsed += new System.Timers.ElapsedEventHandler(timerManager_Elapsed);
                timerManager.Interval = managementInterval < 1000 ? 1000 : managementInterval;  //nov2012: mai meno di 1 sec
                timerManager.Enabled = true;
                //timerManager.Start(); rem nov2012
                LogMessage("Motorola Scanner Manager Service: EXE polling timer started with interval of " + timerManager.Interval + " msec. OnStart-3");

            }
            catch (Exception ex)
            {
                this.EventLog.WriteEntry("Error starting Motorola Scanner Manager Service, message: " + ex.Message);
                this.EventLog.WriteEntry("Error starting Motorola Scanner Manager Service, stack trace: " + ex.StackTrace);
                return;
            }
            LogMessage("Motorola Scanner Manager Service: Started successfully");

        }

        [DllImport("kernel32.dll")]
        private static extern uint WTSGetActiveConsoleSessionId();

        [DllImport("wtsapi32.dll", SetLastError = true)]
        static extern bool WTSQueryUserToken(UInt32 sessionId, out IntPtr Token);

        [DllImport("kernel32.dll", EntryPoint = "CloseHandle", SetLastError = true, CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public extern static bool CloseHandle(IntPtr handle);

        [DllImport("advapi32.dll", EntryPoint = "CreateProcessAsUser", SetLastError = true, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public extern static bool CreateProcessAsUser(IntPtr hToken, String lpApplicationName, String lpCommandLine, ref SECURITY_ATTRIBUTES lpProcessAttributes,
            ref SECURITY_ATTRIBUTES lpThreadAttributes, bool bInheritHandle, int dwCreationFlags, IntPtr lpEnvironment,
            String lpCurrentDirectory, ref STARTUPINFO lpStartupInfo, out PROCESS_INFORMATION lpProcessInformation);

        [DllImport("advapi32.dll", EntryPoint = "DuplicateTokenEx")]
        public extern static bool DuplicateTokenEx(IntPtr ExistingTokenHandle, uint dwDesiredAccess,
            ref SECURITY_ATTRIBUTES lpThreadAttributes, int TokenType,
            int ImpersonationLevel, ref IntPtr DuplicateTokenHandle);


        internal static uint GetSessionId()
        {
            uint result = WTSGetActiveConsoleSessionId();
            if (result == 0xFFFFFFFF)
                throw new InvalidOperationException("No session attached to the physical console.");

            return result;
        }
        [Flags]
        enum Mask : uint
        {
            FILE_READ_DATA = 0x00000001,
            FILE_WRITE_DATA = 0x00000002,
            FILE_APPEND_DATA = 0x00000004,
            FILE_READ_EA = 0x00000008,
            FILE_WRITE_EA = 0x00000010,
            FILE_EXECUTE = 0x00000020,
            FILE_DELETE_CHILD = 0x00000040,
            FILE_READ_ATTRIBUTES = 0x00000080,
            FILE_WRITE_ATTRIBUTES = 0x00000100,

            DELETE = 0x00010000,
            READ_CONTROL = 0x00020000,
            WRITE_DAC = 0x00040000,
            WRITE_OWNER = 0x00080000,
            SYNCHRONIZE = 0x00100000,

            ACCESS_SYSTEM_SECURITY = 0x01000000,
            MAXIMUM_ALLOWED = 0x02000000,

            GENERIC_ALL = 0x10000000,
            GENERIC_EXECUTE = 0x20000000,
            GENERIC_WRITE = 0x40000000,
            GENERIC_READ = 0x80000000
        }

        const uint GENERIC_ALL = 0x10000000;
        const int SecurityImpersonation = 2;
        const int TokenType = 1;

        [StructLayout(LayoutKind.Sequential)]
        public struct STARTUPINFO
        {
            public int cb;
            public String lpReserved;
            public String lpDesktop;
            public String lpTitle;
            public uint dwX;
            public uint dwY;
            public uint dwXSize;
            public uint dwYSize;
            public uint dwXCountChars;
            public uint dwYCountChars;
            public uint dwFillAttribute;
            public uint dwFlags;
            public short wShowWindow;
            public short cbReserved2;
            public IntPtr lpReserved2;
            public IntPtr hStdInput;
            public IntPtr hStdOutput;
            public IntPtr hStdError;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct PROCESS_INFORMATION
        {
            public IntPtr hProcess;
            public IntPtr hThread;
            public uint dwProcessId;
            public uint dwThreadId;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct SECURITY_ATTRIBUTES
        {
            public int Length;
            public IntPtr lpSecurityDescriptor;
            public bool bInheritHandle;
        }

        int motoPID=0;
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        void StartScanManagerApplication()
        {
            //try
            //{
            //    // Chiude eventuali processi aperti in precedenza
            //    CloseHandle(pi.hProcess);
            //    CloseHandle(pi.hThread);
            //}catch(Exception){}

            //Launch UI with Different User Credentials
            uint dwSessionID = WTSGetActiveConsoleSessionId();

            IntPtr hToken = new IntPtr(0);
            IntPtr hDuplicatedToken = new IntPtr(0);
            bool      ret;
            SECURITY_ATTRIBUTES sa  = new SECURITY_ATTRIBUTES();
			sa.bInheritHandle       = false;
			sa.Length               = Marshal.SizeOf(sa);
			sa.lpSecurityDescriptor = (IntPtr)0;

            WTSQueryUserToken(dwSessionID, out hToken);     //DOVREBBE TROVARE IL TOKEN DELL'UTENTE DESKTOP
            //hToken = WindowsIdentity.GetCurrent().Token;  //INUTILE PER I SERVIZI! TROVA SEMPRE LOCALSYSTEM!

            //nov2012: c'è un bug in questo run qnd si effettua LOGOFF dal desktop: il processo figlio viene killato e ricreato con LOCALSYSTEM!
            LogMessage("StartScanManagerApplication: dwSessionID=0x" + dwSessionID.ToString("X") + " hToken=0x" + hToken.ToString("X"));


            ret = DuplicateTokenEx(hToken, GENERIC_ALL, ref sa, SecurityImpersonation, TokenType, ref hDuplicatedToken);

            //NOV2012-check su dupl handle: se zero, Desktop WIndow Manager è assente e processo partirebbe come SYSTEM
            if (hDuplicatedToken.ToInt32() == 0) {
                LogMessage("StartScanManagerApplication: hDuplicatedToken==0 => Could not start child process as desktop user. Trying again later.");
                return;
            }

            si          = new STARTUPINFO();
			si.cb                   = Marshal.SizeOf(si);
			si.lpDesktop            = "";

            string ExeName = ConfigurationSettings.AppSettings["ScannerManagerExecutable"]; // "MotScanManager.exe";
            string ExeFolderPath = System.AppDomain.CurrentDomain.BaseDirectory;//System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().CodeBase);// @"C:\projects\Motorola\dev\20110912 MotoSW (.NET20, Win7 Porting)\service_test\MotorolaScannerManager+WMI+MSM\Release";

            LogMessage("StartScanManagerApplication: Trying to start <" + ExeName + "> from folder <" + ExeFolderPath + "> with User DuplToken <0x" + hDuplicatedToken.ToString("X") + ">");

            pi = new PROCESS_INFORMATION();
            ret = CreateProcessAsUser(hDuplicatedToken, null,   ExeName, 
                                                                ref sa, ref sa, false, 0, (IntPtr)0,
                                                                ExeFolderPath, ref si, out pi);

            if (ret == false)
            {
                motoPID = 0;
                LogMessage("StartScanManagerApplication: CreateProcessAsUser failed with <" + Marshal.GetLastWin32Error() + ">");
            }
            else
            {
                motoPID = (int)pi.dwProcessId;
                LogMessage("StartScanManagerApplication: CreateProcessAsUser SUCCESS. The child PID is <" + pi.dwProcessId + ">");

                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
            }

            ret = CloseHandle(hDuplicatedToken);
        }


        [DllImportAttribute("kernel32.dll", EntryPoint = "OpenProcess")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId); 
        void timerManager_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                timerManager.Enabled=false;    //nov2012
                //LogMessage("timerManager_Elapsed: INIT");
                IntPtr res = OpenProcess(0x00020000, true, motoPID);
                if (res == (IntPtr)0)
                {
                    LogMessage("timerManager_Elapsed: Process <" + motoPID + "> does not exist! Starting a new instance");

                    //RESTART MOTSCANMAN!
                    StartScanManagerApplication();
                }
                else
                {
                    CloseHandle(res);
                }
                //LogMessage("timerManager_Elapsed: END");
                timerManager.Enabled=true;   //nov2012
            }
            catch (Exception ex) { LogMessage("timerManager_Elapsed: EXCEPTION timerManager_Elapsed " + ex.Message); }
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern int TerminateProcess(IntPtr processIdOrHandle, IntPtr exitCode);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool PostThreadMessage(uint threadId, uint msg, UIntPtr wParam, IntPtr lParam);
        protected override void OnStop()
        {
            LogMessage("Motorola Scanner Manager Service: Stopping");            
            try {
                LogMessage("OnStop(), trying to terminate MotScanManager.exe");

                IntPtr res = OpenProcess(0x0001, false, motoPID);
                if (res != (IntPtr)0)
                {
                    int ret = TerminateProcess(res, (IntPtr)0);
                    LogMessage("TerminateProcess returned <"+ret+">");
                }                
            }
            catch (Exception e) { LogMessage("EXCEPTION OnStop "+e.Message); }
        }

    }
}
