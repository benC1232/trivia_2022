using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;
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
    /// Interaction logic for PostGameWindow.xaml
    /// </summary>
    public partial class PostGameWindow : Window
    {
        private DispatcherTimer timer;
        private Communicator comm;
        private int secondsWasted;

        public PostGameWindow(Communicator c)

        {
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            this.secondsWasted = 0;
            this.countdown.Content = 30.ToString();
            this.comm = c;
            this.timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1)
            };
            timer.Tick += timer_Tick;
            this.timer.Start();
            this.refresh();
        }

        private void refresh()
        {
            var arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(17, arr);
            var response = this.comm.Recieve();
            if (response.Item1 == 17)
            {
                var getGameResultsResponse = JsonConvert.DeserializeObject<responseStructs.GetGameResultsResponse>(Encoding.UTF8.GetString(response.Item2));
                string[] players = getGameResultsResponse.results.Split(',');
                List<string> items = new List<string>();

                for (int i = 0; i < players.Length; i++)
                {
                    players[i] = i.ToString() + ". " + players[i];
                }
                string leaderboard = String.Join("\n", players);
                this.PlayersTxtBlck.Text = leaderboard;
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            this.countdown.Content = Int32.Parse(this.countdown.Content.ToString()) - 1;
            this.secondsWasted++;
            if ((secondsWasted)%3==0)
            {
                this.refresh();
                
            }
            if (this.secondsWasted == 30)
            {
                this.leave();
            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            this.leave();
        }

        private void leave()
        {
            var arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(14, arr);
            var response = this.comm.Recieve();
            if (response.Item1 == 14)
            {
                this.comm.leaveGameFlag = false;
                var menuWindow = new MenuWindow(this.comm);
                this.Close();
                menuWindow.Show();
            }
            else if (response.Item1 == 3)
            {
                var errResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(Encoding.ASCII.GetString(response.Item2));
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errResponse.message;
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.comm.Disconnect();
            e.Cancel = false;
        }
    }
}