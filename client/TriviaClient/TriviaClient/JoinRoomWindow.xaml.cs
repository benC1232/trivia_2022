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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        private Communicator comm;
        private DispatcherTimer timer;

        public JoinRoomWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            refresh();
            timer = new System.Windows.Threading.DispatcherTimer();
            timer.Tick += new EventHandler(dispatcherTimer_Tick);
            timer.Interval = new TimeSpan(0, 0, 3);
            timer.Start();
            
        }

        private void refresh()
        {
            this.errorLbl.Visibility = Visibility.Hidden;
            byte[] data = new byte[1];
            data[0] = 0;
            this.comm.Send(4, data);
            Tuple<int, byte[]> response = this.comm.Recieve();

            string strResponse = Encoding.ASCII.GetString(response.Item2);
            if (response.Item1 == 5)
            {
                responseStructs.GetRoomResponse getRoomResponse = JsonConvert.DeserializeObject<responseStructs.GetRoomResponse>(strResponse);

                List<string> items = new List<string>(getRoomResponse.rooms.Split(','));
                if (items[0] == "no rooms available")
                {
                    this.errorLbl.Visibility = Visibility.Visible;
                    this.errorLbl.Text = "no rooms available";
                }
                else
                {
                    this.roomsListLstBx.ItemsSource = items;
                }
            }
            if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errorResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(strResponse);
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errorResponse.message;
            }
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            refresh();
        }


        private void JoinRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            String selectedRoomName = this.roomsListLstBx.SelectedItem.ToString();
            this.errorLbl.Visibility = Visibility.Visible;
            timer.Stop();
            this.errorLbl.Text = "joining rooms hasnt been implemented yet";
        }

        private void roomsListLstBx_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            this.JoinRoomBtn.Content = "Join " + this.roomsListLstBx.SelectedItem.ToString();
        }
    }
}