using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Slaughter_Friends_Launcher.Logic.Helpers
{
    internal class IniKeyValuePairsBuilder
    {
        public string BuildBooleanKey(string key, bool booleanTrue)
        {
            string keyValuePairStringed;
            if (booleanTrue)
            {
                keyValuePairStringed = key + "=1";
            }
            else
            {
                keyValuePairStringed = key + "=0";
            }
            return keyValuePairStringed;
        }

    }
}
