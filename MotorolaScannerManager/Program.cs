using System;
using System.Collections.Generic;
using System.ServiceProcess;
using System.Text;

namespace MotorolaScannerManager
{
    static class Program
    {
        /// <summary> 
        /// The main entry point for the application.
        /// </summary>
        static void Main()
        {
#if (!DEBUG)
            ServiceBase[] ServicesToRun;
            ServicesToRun = new ServiceBase[] 
			{ 
				new ScannerManagerService() 
			};
            ServiceBase.Run(ServicesToRun);
#else
            string[] szArg = { "" };

            ScannerManagerService service = new ScannerManagerService();
            //service.OnStart(szArg);
            System.Threading.Thread.Sleep(System.Threading.Timeout.Infinite);
#endif
        }


    }
}
