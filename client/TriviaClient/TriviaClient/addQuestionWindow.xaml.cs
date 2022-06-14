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
    public partial class addQuestionWindow : Window
    {
        private Communicator comm;

        public addQuestionWindow(Communicator c)
        {
            InitializeComponent();
            this.comm = c;
            this.errorLbl.Visibility = Visibility.Hidden;
        }

        private void CreateBtn_OnClick(object sender, RoutedEventArgs e)
        {
            if (this.Question.Text == "" || this.CorrectAnswer.Text == "" || this.WrongAnswer1.Text == "" || this.WrongAnswer2.Text == "" || this.WrongAnswer3.Text == "")
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = "Please fill in all fields";
            }
            else
            {
                requestStructs.AddQuestionRequest addQuestionRequest;
                addQuestionRequest.question = this.Question.Text;
                addQuestionRequest.correctAnswer = this.CorrectAnswer.Text;
                addQuestionRequest.wrongAnswer1 = this.WrongAnswer1.Text;
                addQuestionRequest.wrongAnswer2 = this.WrongAnswer2.Text;
                addQuestionRequest.wrongAnswer3 = this.WrongAnswer3.Text;
                string json = JsonConvert.SerializeObject(addQuestionRequest);
                byte[] data = Encoding.ASCII.GetBytes(json);
                this.comm.Send(20, data);
                Tuple<int, byte[]> response = this.comm.Recieve();
                if (response.Item1 == 20)
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

        private void BackToMenuBtn_OnClick(object sender, RoutedEventArgs e)
        {
            var menuWindow = new MenuWindow(this.comm);
            this.Close();
            menuWindow.Show();
        }
    }
}