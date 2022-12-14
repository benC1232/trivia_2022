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
    /// Interaction logic for waitingRoomAdmin.xaml
    /// </summary>
    public partial class WaitingRoomAdmin : Window
    {
        private Communicator comm;
        private DispatcherTimer timer;
        private roomStruct room;

        public WaitingRoomAdmin(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            timer = new System.Windows.Threading.DispatcherTimer();
            timer.Tick += new EventHandler(dispatcherTimer_Tick);
            timer.Interval = new TimeSpan(0, 0, 3);
            timer.Start();
            refresh();
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
                if (roomState.hasGameBegun)
                {
                    this.comm.closeRoomFlag = false;
                    this.comm.leaveGameFlag = true;
                    this.timer.Stop();
                    gameWindow GameWindow = new gameWindow(this.comm, room);
                    this.Close();
                    GameWindow.Show();
                }
            }
            else if (response.Item1 == 3)
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

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            this.timer.Stop();
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(10, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            string strResponse = Encoding.UTF8.GetString(response.Item2);
            if (response.Item1 == 10)
            {
                this.comm.closeRoomFlag = false;
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

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            this.timer.Stop();
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(11, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            if (response.Item1 == 11)
            {
                this.comm.closeRoomFlag = false;
                this.comm.leaveGameFlag = true;
                gameWindow GameWindow = new gameWindow(this.comm, room);
                this.Close();
                GameWindow.Show();
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errorResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(Encoding.UTF8.GetString(response.Item2));
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