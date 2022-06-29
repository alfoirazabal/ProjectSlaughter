using Slaughter_Friends_Launcher.Logic;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Slaughter_Friends_Launcher
{
    public partial class MainForm : Form
    {

        private readonly SettingsFileLogic SettingsFileLogic;

        public MainForm()
        {
            InitializeComponent();
            this.SettingsFileLogic = new SettingsFileLogic();
            this.CbxUseControllerForP2.Checked = this.SettingsFileLogic.IsUseControllerForP2Enabled();
        }

        private void CbxUseControllerForP2_CheckedChanged(object sender, EventArgs e)
        {
            this.SettingsFileLogic.SetUseControllerForP2Enabled(this.CbxUseControllerForP2.Checked);
        }

        private void BtnStart_Click(object sender, EventArgs e)
        {
            string startupPath = Application.StartupPath;
            string gamePath = startupPath + "\\" + ConfigurationManager.AppSettings["ExecutableRelativePath"];
            try
            {
                Process.Start(gamePath);
                Application.Exit();
            }
            catch (Exception exception)
            {
                if (exception is Win32Exception || exception is FileNotFoundException)
                {
                    MessageBox.Show(
                        this,
                        "Could not find file: " + gamePath + "\nCheck variable 'ExecutableRelativePath' on App.config",
                        "Error",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );
                }
                else
                {
                    throw exception;
                }
            }
        }
    }
}
