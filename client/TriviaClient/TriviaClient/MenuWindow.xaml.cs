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
    /// Interaction logic for MenuWindow.xaml
    /// </summary>
    public partial class MenuWindow : Window
    {
        private Communicator comm;

        public MenuWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
        }

        private void QuitBtn_Click(object sender, RoutedEventArgs e)
        {
            this.comm.Disconnect();
            Application.Current.Shutdown();
        }

        private void CreateRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow createRoomWindow = new CreateRoomWindow(this.comm);
            this.Close();
            createRoomWindow.Show();
        }

        private void JoinRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            JoinRoomWindow joinRoomWindow = new JoinRoomWindow(this.comm);
            this.Close();
            joinRoomWindow.Show();
        }

        private void personalRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            personalStatsWindow personalStatsWindow = new personalStatsWindow(this.comm);
            this.Close();
            personalStatsWindow.Show();
        }

        private void leaderBoardRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            leaderBoardWindow leaderBoardWindow = new leaderBoardWindow(this.comm);
            this.Close();
            leaderBoardWindow.Show();
        }

        private void AddQuestionBtn_OnClick(object sender, RoutedEventArgs e)
        {
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.comm.Disconnect();
            e.Cancel = false;
        }
    }
}