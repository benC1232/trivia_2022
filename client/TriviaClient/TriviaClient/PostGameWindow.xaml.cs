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

        public PostGameWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromSeconds(1)
            };
            timer.Tick += timer_Tick;
            var arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(17, arr);
            var response = this.comm.Recieve();
            if (response.Item1 == 17)
            {
                var getGameResultsResponse = JsonConvert.DeserializeObject<responseStructs.GetGameResultsResponse>(Encoding.UTF8.GetString(response.Item2));
                var players = getGameResultsResponse.results.Split(',');
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            this.countdown.Content = 30 - DateTime.Now.Second;
            if (DateTime.Now.Second == 30)
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
    }
}