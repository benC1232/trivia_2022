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
    /// Interaction logic for personalStatsWindow.xaml
    /// </summary>
    public partial class personalStatsWindow : Window
    {
        private Communicator comm;

        public personalStatsWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            byte[] data = new byte[1];
            data[0] = 0;
            comm.Send(7, data);
            Tuple<int, byte[]> response = this.comm.Recieve();
            string strResponse = Encoding.ASCII.GetString(response.Item2);
            if (response.Item1 == 9)
            {
                responseStructs.GetPersonalStatsResponse getPersonalStatsResponse = JsonConvert.DeserializeObject<responseStructs.GetPersonalStatsResponse>(strResponse);

                string[] parsedResponse = getPersonalStatsResponse.stats.Split(',');
                string avgTime = parsedResponse[0].Split(':')[1];
                this.avgTimePerAnswerLbl.Content = avgTime;
                string correctAnswers = parsedResponse[1].Split(':')[1];
                this.NumOfCorrectAnswersLbl.Content = correctAnswers;
                string totalAnswers = parsedResponse[2].Split(':')[1];
                this.NumOfAnswersLbl.Content = totalAnswers;
                string gameNum = parsedResponse[3].Split(':')[1];
                this.NumOfGamesLbl.Content = gameNum;
            }
            if (response.Item1 == 3)
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = strResponse;
            }
        }

        private void backToMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(this.comm);
            this.Close();
            menuWindow.Show();
        }
    }
}