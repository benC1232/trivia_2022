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
            this.secondsWasted = 0;
            this.countdown.Content = 30;
            this.comm = c;
            InitializeComponent();
            this.timer = new DispatcherTimer();
            this.timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += timer_Tick;
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(17, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            if (response.Item1 == 17)
            {
                responseStructs.GetGameResultsResponse getGameResultsResponse = JsonConvert.DeserializeObject<responseStructs.GetGameResultsResponse>(Encoding.UTF8.GetString(response.Item2));
                string[] players = getGameResultsResponse.results.Split(',');
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            this.countdown.Content = Int32.Parse(this.countdown.Content.ToString()) - 1;
            this.secondsWasted++;
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
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(14, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            if (response.Item1 == 14)
            {
                MenuWindow menuWindow = new MenuWindow(this.comm);
                this.Close();
                menuWindow.Show();
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(Encoding.ASCII.GetString(response.Item2));
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errResponse.message;
            }
        }
    }
}