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
    public partial class waitingRoom : Window
    {
        private Communicator comm;
        private DispatcherTimer timer;
        private roomStruct room;

        public waitingRoom(Communicator c)
        {
            this.comm = c;
            //💻 - paste it before the admin username
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
                string playerText = "";
                playerText = System.String.Join("\n", players);
                playerText = "💻 admin -" + playerText;
                this.PlayersTxtBlck.Text = playerText;
                if (roomState.hasGameBegun == 1)
                {
                    this.timer.Stop();
                    gameWindow GameWindow = new gameWindow(this.comm);
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

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                refresh();
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
    }
}