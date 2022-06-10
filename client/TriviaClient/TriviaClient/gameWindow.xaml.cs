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
    /// Interaction logic for gameWindow.xaml
    /// </summary>
    public partial class gameWindow : Window
    {
        private Communicator comm;
        private DispatcherTimer timer;
        private int totalSeconds;
        private int secondsWasted;
        private int correctAnswerCount;
        private int questionsLeft;

        public gameWindow(Communicator c, roomStruct room)
        {
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;

            this.timer = new DispatcherTimer();
            this.timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += timer_Tick;
            this.comm = c;
            this.correctAnswerCount = 0;
            //does not need to be 0!!! needs to be the initial amount of question
            this.questionsLeft = room.questionCount;
            this.qCount.Content = this.questionsLeft;
            this.totalSeconds = room.answerTimeout;
            this.getQuestion();
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            this.secondsWasted++;
            this.countdown.Content = totalSeconds - this.secondsWasted;
            if (totalSeconds - this.secondsWasted == 0)
            {
                submitAnswer("never gonna give you up");
                if (!this.getQuestion())
                {
                    this.timer.Stop();
                    PostGameWindow postGameWindow = new PostGameWindow(this.comm);
                    this.Close();
                    postGameWindow.Show();
                }
            }
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
        }

        private async void Answer1_Click(object sender, RoutedEventArgs e)
        {
            this.Answer1.Background = submitAnswer(this.Answer1.Content.ToString()) ? new SolidColorBrush(Colors.Green) : new SolidColorBrush(Colors.Red);
            await Task.Delay(2000);
            if (!this.getQuestion())
            {
                this.timer.Stop();
                var postGameWindow = new PostGameWindow(this.comm);
                this.Close();
                postGameWindow.Show();
            }
        }

        private async void Answer2_Click(object sender, RoutedEventArgs e)
        {
            if (submitAnswer(this.Answer2.Content.ToString()))
            {
                this.Answer2.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                this.Answer2.Background = new SolidColorBrush(Colors.Red);
            }
            await Task.Delay(2000);
            if (!this.getQuestion())
            {
                this.timer.Stop();
                var postGameWindow = new PostGameWindow(this.comm);
                this.Close();
                postGameWindow.Show();
            }
        }

        private async void Answer3_Click(object sender, RoutedEventArgs e)
        {
            if (submitAnswer(this.Answer3.Content.ToString()))
            {
                this.Answer3.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                this.Answer3.Background = new SolidColorBrush(Colors.Red);
            }
            await Task.Delay(2000);
            if (!this.getQuestion())
            {
                this.timer.Stop();
                PostGameWindow postGameWindow = new PostGameWindow(this.comm);
                this.Close();
                postGameWindow.Show();
            }
        }

        private async void Answer4_Click(object sender, RoutedEventArgs e)
        {
            if (submitAnswer(this.Answer4.Content.ToString()))
            {
                this.Answer4.Background = new SolidColorBrush(Colors.Green);
            }
            else
            {
                this.Answer4.Background = new SolidColorBrush(Colors.Red);
            }
            await Task.Delay(2000);
            if (!this.getQuestion())
            {
                this.timer.Stop();
                PostGameWindow postGameWindow = new PostGameWindow(this.comm);
                this.Close();
                postGameWindow.Show();
            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
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

        private bool submitAnswer(string answer)
        {
            this.timer.Stop();
            requestStructs.SubmitAnswerRequest request;
            request.answer = answer;
            request.responseTime = this.secondsWasted;
            this.secondsWasted = 0;
            string json = JsonConvert.SerializeObject(request);
            byte[] data = Encoding.ASCII.GetBytes(json);
            this.comm.Send(16, data);
            Tuple<int, byte[]> response = this.comm.Recieve();
            if (response.Item1 == 16)
            {
                responseStructs.SubmitAnswerResponse responseStruct = JsonConvert.DeserializeObject<responseStructs.SubmitAnswerResponse>(Encoding.ASCII.GetString(response.Item2));
                if (responseStruct.isCorrect)
                {
                    this.correctAnswerCount++;
                    this.correctAnswers.Content = this.correctAnswerCount;
                }
                return responseStruct.isCorrect;
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(Encoding.ASCII.GetString(response.Item2));
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errResponse.message;
            }
            return false;
        }

        private bool getQuestion()
        {
            byte[] arr = new byte[1];
            arr[0] = 1;
            this.comm.Send(15, arr);
            Tuple<int, byte[]> response = this.comm.Recieve();
            if (response.Item1 == 15)
            {
                responseStructs.GetQuestionResponse responseStruct = JsonConvert.DeserializeObject<responseStructs.GetQuestionResponse>(Encoding.ASCII.GetString(response.Item2));
                this.question.Text = responseStruct.question;
                string[] answers = responseStruct.answers.Split(',');
                this.Answer1.Content = answers[0];
                this.Answer2.Content = answers[1];
                this.Answer3.Content = answers[2];
                this.Answer4.Content = answers[3];
                this.countdown.Content = totalSeconds;
                this.secondsWasted = 0;
                this.questionsLeft--;
                this.qCount.Content = this.questionsLeft;

                this.timer.Start();
                return responseStruct.status == 1;
            }
            else if (response.Item1 == 3)
            {
                responseStructs.ErrorResponse errResponse = JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(Encoding.ASCII.GetString(response.Item2));
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = errResponse.message;
            }
            return false;
        }
    }
}