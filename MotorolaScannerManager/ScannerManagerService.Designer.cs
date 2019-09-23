namespace MotorolaScannerManager
{
    partial class ScannerManagerService
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
            this.timerManager = new System.Timers.Timer();
            ((System.ComponentModel.ISupportInitialize)(this.timerManager)).BeginInit();
            // 
            // timerManager
            // 
            this.timerManager.Enabled = true;
            this.timerManager.Interval = 1000;
            // 
            // ScannerManagerService
            // 
            this.ServiceName = "MotorolaScannerManagerService";
            ((System.ComponentModel.ISupportInitialize)(this.timerManager)).EndInit();

        }

        #endregion

        private System.Timers.Timer timerManager;
    }
}
