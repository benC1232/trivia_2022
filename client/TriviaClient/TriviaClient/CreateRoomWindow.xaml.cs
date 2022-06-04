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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        private Communicator comm;

        public CreateRoomWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
        }

        private void CreateBtn_Click(object sender, RoutedEventArgs e)
        {
            if (this.RoomName.Text == "")
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = "Please enter a room name";
                return;
            }
            requestStructs.CreateRoomRequest request;
            request.roomName = this.RoomName.Text;
            request.maxUsers = (int)this.MaxPlayers.Value;
            request.questionCount = (int)this.numOfQuestions.Value;
            request.answerTimeout = (int)this.TimeQuestions.Value;
            string json = JsonConvert.SerializeObject(request);
            byte[] data = Encoding.ASCII.GetBytes(json);
            this.comm.Send(3, data);
            Tuple<int, byte[]> response = comm.Recieve();
            string strResponse = Encoding.ASCII.GetString(response.Item2);
            if (response.Item1 == 8)
            {
                waitingRoomAdmin waitingroomwindow = new waitingRoomAdmin(this.comm);
                waitingroomwindow.Show();
                this.Close();
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(Encoding.ASCII.GetString(response.Item2));
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errResponse.message;
            }
            else
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = "" + response.Item1;
            }
        }

        private void backToMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(comm);
            this.Close();
            menuWindow.Show();
        }
    }
}