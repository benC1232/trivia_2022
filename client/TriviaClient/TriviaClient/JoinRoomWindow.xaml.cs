using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Threading;

using System.Windows;
using System.Windows.Controls;

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
                string[] rooms = getRoomResponse.rooms.Split(',');

                List<string> items = new List<string>();

                if (rooms[0] == "no rooms available")
                {
                    this.errorLbl.Visibility = Visibility.Visible;
                    this.errorLbl.Text = "no rooms available";
                }
                else
                {
                    for (int i = 0; i < rooms.Length - 1; i++)
                    {
                        string[] parsedResponse = rooms[i].Split(':');
                        string roomName = parsedResponse[0];
                        string roomId = parsedResponse[1];
                        string result = roomName + " id: " + roomId;
                        items.Add(result);
                    }
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
            this.timer.Stop();
            string selectedRoomName = this.roomsListLstBx.SelectedItem.ToString();
            string parsedResponse = selectedRoomName.Split(':')[1];
            parsedResponse = parsedResponse.Substring(1);
            requestStructs.JoinRoomRequest joinRoomRequest;
            joinRoomRequest.roomId = parsedResponse;
            string json = JsonConvert.SerializeObject(joinRoomRequest);
            byte[] data = Encoding.ASCII.GetBytes(json);
            this.comm.Send(6, data);
            Tuple<int, byte[]> response = this.comm.Recieve();
            string strResponse = Encoding.ASCII.GetString(response.Item2);
            if (response.Item1 == 7)
            {
                WaitingRoom waitingroomwindow = new WaitingRoom(this.comm);
                this.Close();
                waitingroomwindow.Show();
            }
            else
            {
                responseStructs.ErrorResponse errorResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(strResponse);
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errorResponse.message;
            }
        }

        private void roomsListLstBx_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            this.JoinRoomBtn.Content = "Join " + this.roomsListLstBx.SelectedItem.ToString();
        }

        private void backToMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            this.timer.Stop();
            MenuWindow menuWindow = new MenuWindow(comm);
            this.Close();
            menuWindow.Show();
        }
    }
}