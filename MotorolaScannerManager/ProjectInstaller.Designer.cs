namespace MotorolaScannerManager
{
    partial class ProjectInstaller
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.MotorolaServiceProcessInstaller = new System.ServiceProcess.ServiceProcessInstaller();
            this.MotorolaServiceInstaller = new System.ServiceProcess.ServiceInstaller();
            // 
            // MotorolaServiceProcessInstaller
            // 
            this.MotorolaServiceProcessInstaller.Account = System.ServiceProcess.ServiceAccount.LocalSystem;
            this.MotorolaServiceProcessInstaller.Password = null;
            this.MotorolaServiceProcessInstaller.Username = null;
            // 
            // MotorolaServiceInstaller
            // 
            this.MotorolaServiceInstaller.Description = "Manage the Motorola Scanner Manager process";
            this.MotorolaServiceInstaller.DisplayName = "Motorola Scanner Manager Service";
            this.MotorolaServiceInstaller.ServiceName = "MotorolaScannerManagerService";
            this.MotorolaServiceInstaller.StartType = System.ServiceProcess.ServiceStartMode.Automatic;
            // 
            // ProjectInstaller
            // 
            this.Installers.AddRange(new System.Configuration.Install.Installer[] {
            this.MotorolaServiceProcessInstaller,
            this.MotorolaServiceInstaller});

        }

        #endregion

        private System.ServiceProcess.ServiceProcessInstaller MotorolaServiceProcessInstaller;
        private System.ServiceProcess.ServiceInstaller MotorolaServiceInstaller;
    }
}