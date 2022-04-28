using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NZ8
{
    public partial class Form1 : Form
    {
        private string username = "user";
        private string password = "user";
        private string ipAddress = "192.168.1.116";
        private string port = "21";
        private string fileName = "textFile1.txt";
        private string ServerPath
        {
            get { return "ftp://" + ipAddress + ":" + port; }
            set { }
        }

        public Form1()
        {
            InitializeComponent();

            textBoxUsername.Text = username;
            textBoxPassword.Text = password;
            textBoxIpAddress.Text = ipAddress;
            textBoxPort.Text = port;
            textBoxFileName.Text = fileName;
        }

        private void ReadTextBoxInputs()
        {
            username = textBoxUsername.Text;
            password = textBoxPassword.Text;
            ipAddress = textBoxIpAddress.Text;
            port = textBoxPort.Text;
            fileName = textBoxFileName.Text;
        }

        private void RichTextBoxLog_WriteLine(string text = "")
        {
            richTextBoxLog.Text += text + "\n";
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            ReadTextBoxInputs();


            GetDataFromFTPServer();
        }

        private void GetDataFromFTPServer()
        {
            string downloadingFile = ServerPath + "/" + fileName;
            RichTextBoxLog_WriteLine("Downloading... " + downloadingFile);

            try
            {
                String result = String.Empty;
                FtpWebRequest request = (FtpWebRequest)WebRequest.Create(downloadingFile);
                request.Method = WebRequestMethods.Ftp.DownloadFile;
                request.Credentials = new NetworkCredential(username, password);

                FtpWebResponse response = (FtpWebResponse)request.GetResponse();
                Stream responseStream = response.GetResponseStream();
                StreamReader reader = new StreamReader(responseStream);

                result += reader.ReadToEnd();

                reader.Close();
                response.Close();

                RichTextBoxLog_WriteLine("File downloaded successfully.");
                SaveFileLocally(result);
            }
            catch (Exception e)
            {
                RichTextBoxLog_WriteLine(e.Message);
            }
        }

        private void SaveFileLocally(String content)
        {
            try
            {
                string savePath = Directory.CreateDirectory("FTP").FullName;
                
                using (StreamWriter file = File.CreateText(savePath + "/" + fileName))
                {
                    file.WriteLine(content);
                    file.Close();
                }
                RichTextBoxLog_WriteLine("File saved to: " + savePath);
            }
            catch (Exception e)
            {
                RichTextBoxLog_WriteLine(e.Message);
            }
        }
    }
}
