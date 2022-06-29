using Slaughter_Friends_Launcher.Logic.Helpers;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Slaughter_Friends_Launcher.Logic
{
    internal class SettingsFileLogic
    {

        private static readonly string USE_CONTROLLER_KEY = "UseControllerForPlayer2";

        private readonly IniKeyValuePairsBuilder KeyValuePairsBuilder;

        private readonly string SettingsFilePath;
        private readonly List<string> SettingsFileLines;

        private List<string> ReadSettingsFile()
        {
            return File.ReadAllLines(this.SettingsFilePath).ToList();
        }

        private void UpdateSettingsFile()
        {
            File.WriteAllLines(this.SettingsFilePath, this.SettingsFileLines);
        }

        public SettingsFileLogic()
        {
            this.KeyValuePairsBuilder = new IniKeyValuePairsBuilder();
            string localAppDataPath = Environment.GetEnvironmentVariable("localappdata");
            string settingsPath = ConfigurationManager.AppSettings["SettingsLocalAppDataPath"];
            string settingsFileName = ConfigurationManager.AppSettings["SettingsFileName"];
            this.SettingsFilePath = localAppDataPath + "\\" + settingsPath + "\\" + settingsFileName;
            if (!File.Exists(this.SettingsFilePath))
            {
                Directory.CreateDirectory(localAppDataPath + "\\" + settingsPath);
                string defaultConfigurationText = "[/Script/ConceptDemo.DemoGameInstance]\r\nUseControllerForPlayer2=0";
                File.WriteAllText(this.SettingsFilePath, defaultConfigurationText);
            }
            this.SettingsFileLines = this.ReadSettingsFile();
        }

        public bool IsUseControllerForP2Enabled()
        {
            string UseControllerLine = this.SettingsFileLines.Where(s => s.StartsWith(USE_CONTROLLER_KEY)).FirstOrDefault();
            UseControllerLine = UseControllerLine.Replace(USE_CONTROLLER_KEY + "=", "");
            return UseControllerLine.Equals("1");
        }

        public void SetUseControllerForP2Enabled(bool useControllerForP2)
        {
            string useControllerStringed = this.KeyValuePairsBuilder.BuildBooleanKey(USE_CONTROLLER_KEY, useControllerForP2);
            int useControllerLineIndex = this.SettingsFileLines.FindIndex(e => e.StartsWith(USE_CONTROLLER_KEY));
            if (useControllerLineIndex != -1)
            {
                this.SettingsFileLines[useControllerLineIndex] = useControllerStringed;
            }
            else
            {
                this.SettingsFileLines.Add(useControllerStringed);
            }
            this.UpdateSettingsFile();
        }

    }
}
