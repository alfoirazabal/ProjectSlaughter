
namespace Slaughter_Friends_Launcher
{
    partial class MainForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.BtnStart = new System.Windows.Forms.Button();
            this.CbxUseControllerForP2 = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.LblLauncherVersion = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // BtnStart
            // 
            this.BtnStart.Location = new System.Drawing.Point(101, 201);
            this.BtnStart.Name = "BtnStart";
            this.BtnStart.Size = new System.Drawing.Size(123, 35);
            this.BtnStart.TabIndex = 0;
            this.BtnStart.Text = "Start";
            this.BtnStart.UseVisualStyleBackColor = true;
            this.BtnStart.Click += new System.EventHandler(this.BtnStart_Click);
            // 
            // CbxUseControllerForP2
            // 
            this.CbxUseControllerForP2.AutoSize = true;
            this.CbxUseControllerForP2.BackColor = System.Drawing.Color.Yellow;
            this.CbxUseControllerForP2.Location = new System.Drawing.Point(101, 166);
            this.CbxUseControllerForP2.Name = "CbxUseControllerForP2";
            this.CbxUseControllerForP2.Size = new System.Drawing.Size(123, 17);
            this.CbxUseControllerForP2.TabIndex = 1;
            this.CbxUseControllerForP2.Text = "Use Controller for P2";
            this.CbxUseControllerForP2.UseVisualStyleBackColor = false;
            this.CbxUseControllerForP2.CheckedChanged += new System.EventHandler(this.CbxUseControllerForP2_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(98, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Launcher version:";
            // 
            // LblLauncherVersion
            // 
            this.LblLauncherVersion.AutoSize = true;
            this.LblLauncherVersion.Location = new System.Drawing.Point(211, 0);
            this.LblLauncherVersion.Name = "LblLauncherVersion";
            this.LblLauncherVersion.Size = new System.Drawing.Size(13, 13);
            this.LblLauncherVersion.TabIndex = 3;
            this.LblLauncherVersion.Text = "1";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Slaughter_Friends_Launcher.Properties.Resources.BackgroundImage;
            this.ClientSize = new System.Drawing.Size(312, 248);
            this.Controls.Add(this.LblLauncherVersion);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CbxUseControllerForP2);
            this.Controls.Add(this.BtnStart);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(328, 287);
            this.MinimumSize = new System.Drawing.Size(328, 287);
            this.Name = "MainForm";
            this.Text = "Slaughter Friends";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BtnStart;
        private System.Windows.Forms.CheckBox CbxUseControllerForP2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label LblLauncherVersion;
    }
}

