using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace sign_csp
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// Please not that from eidmw 3.5.4 onwards, the CSP is not installed
        /// on OS's beyond Windows XP (e.g. Vista, 7)
        /// Instead, the minidriver is installed 
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}