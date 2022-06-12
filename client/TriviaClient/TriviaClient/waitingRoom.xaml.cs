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
using System.ComponentModel;

namespace TriviaClient
{
    public partial class WaitingRoom : Window
    {
        private Communicator comm;
        private DispatcherTimer timer;
        private roomStruct room;

        public WaitingRoom(Communicator c)
        {
            this.comm = c;
            //💻 - paste it before the admin username
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            timer = new System.Windows.Threading.DispatcherTimer();
            timer.Tick += new EventHandler(DispatcherTimer_Tick);
            timer.Interval = new TimeSpan(0, 0, 3);
            timer.Start();
            Refresh();
        }

        private void Refresh()
        {
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(12, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            string strResponse = Encoding.UTF8.GetString(response.Item2);
            if (response.Item1 == 12)
            {
                responseStructs.GetRoomStateResponse roomState = JsonConvert.DeserializeObject<responseStructs.GetRoomStateResponse>(strResponse);
                this.room.answerTimeout = roomState.answerTimeout;
                this.room.hasGameBegun = roomState.hasGameBegun;
                this.room.questionCount = roomState.questionCount;
                string[] players = roomState.players.Split(',');
                string playerText = System.String.Join("\n", players);
                playerText = "💻 admin -" + playerText;
                this.PlayersTxtBlck.Text = playerText;
                if (roomState.hasGameBegun)
                {
                    this.timer.Stop();
                    gameWindow GameWindow = new gameWindow(this.comm, room);
                    this.Close();
                    GameWindow.Show();
                }
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errorResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(strResponse);
                if (errorResponse.message.CompareTo("std::bad_alloc was thrown while handling request [room member request handler]") == 0)
                {
                    throw new Exception("room has been closed");
                }
                else
                {
                    this.errorLbl.Visibility = Visibility.Visible;
                    this.errorLbl.Text = errorResponse.message;
                }
            }
        }

        private void DispatcherTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                Refresh();
            }
            catch
            {
                this.timer.Stop();
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = "room has been closed";
                MenuWindow menuWindow = new MenuWindow(this.comm);
                this.Close();
                menuWindow.Show();
                this.Close();
            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            this.timer.Stop();
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(13, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            string strResponse = Encoding.UTF8.GetString(response.Item2);
            if (response.Item1 == 13)
            {
                this.comm.leaveRoomFlag = false;
                this.comm.leaveGameFlag = true;
                MenuWindow menuWindow = new MenuWindow(this.comm);
                this.Close();
                menuWindow.Show();
                this.Close();
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errorResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(strResponse);
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errorResponse.message;
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