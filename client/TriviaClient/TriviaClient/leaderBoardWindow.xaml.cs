using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Newtonsoft.Json;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for leaderBoardWindow.xaml
    /// </summary>
    public partial class leaderBoardWindow : Window
    {
        private Communicator comm;

        public leaderBoardWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            byte[] data = new byte[1];
            data[0] = 0;
            comm.Send(10, data);
            Tuple<int, byte[]> response = this.comm.Recieve();
            string strResponse = Encoding.ASCII.GetString(response.Item2);
            if (response.Item1 == 10)
            {
                responseStructs.HighScoreResponse highScoresResponse = JsonConvert.DeserializeObject<responseStructs.HighScoreResponse>(strResponse);
                string[] splitted = highScoresResponse.highscores.Split(',');
                for (int i = 0; i < splitted.Length; i++)
                {
                    switch (i)
                    {
                        case 0:
                            this.first.Content = this.first.Content += splitted[i];
                            break;

                        case 1:
                            this.second.Content = this.second.Content += splitted[i];
                            break;

                        case 2:
                            this.third.Content = this.third.Content += splitted[i];
                            break;

                        case 3:
                            this.fourth.Content = this.fourth.Content += splitted[i];
                            break;

                        case 4:
                            this.fifth.Content = this.fifth.Content += splitted[i];
                            break;
                    }
                }
            }
            if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errorResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(strResponse);
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errorResponse.message;
            }
        }

        private void backToMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(comm);
            this.Close();
            menuWindow.Show();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.comm.Disconnect();
            e.Cancel = false;
        }
    }
}