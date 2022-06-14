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
using System.Windows.Navigation;
using System.Windows.Shapes;

//json library do not delete!!!
using Newtonsoft.Json;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool login;
        private Communicator comm;

        public MainWindow()
        {
            InitializeComponent();
            this.comm = new Communicator();
            this.UsernamePanel.Visibility = Visibility.Hidden;
            this.PasswordPanel.Visibility = Visibility.Hidden;
            this.EmailPanel.Visibility = Visibility.Hidden;
            this.errorLbl.Visibility = Visibility.Hidden;
            try
            {
                comm.Connect();
            }
            catch (Exception e)
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = e.Message;
                return;
            }
        }

        public MainWindow(Communicator c)
        {
            InitializeComponent();
            this.comm = c;
            this.UsernamePanel.Visibility = Visibility.Hidden;
            this.PasswordPanel.Visibility = Visibility.Hidden;
            this.EmailPanel.Visibility = Visibility.Hidden;
            this.errorLbl.Visibility = Visibility.Hidden;
            try
            {
                comm.Connect();
            }
            catch (Exception e)
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = e.Message;
                return;
            }
        }

        private void LogInBtn_Click(object sender, RoutedEventArgs e)
        {
            this.login = true;
            this.UsernamePanel.Visibility = Visibility.Visible;
            this.PasswordPanel.Visibility = Visibility.Visible;
            this.EmailPanel.Visibility = Visibility.Hidden;
        }

        private void SignUpBtn_Click(object sender, RoutedEventArgs e)
        {
            this.login = false;
            this.UsernamePanel.Visibility = Visibility.Visible;
            this.PasswordPanel.Visibility = Visibility.Visible;
            this.EmailPanel.Visibility = Visibility.Visible;
        }

        private void SubmitBtn_Click(object sender, RoutedEventArgs e)
        {
            //checking for errors
            if (!this.comm.connected)
            {
                this.errorLbl.Visibility = Visibility.Visible;
                this.errorLbl.Text = "cant submit, you are not connected";
            }
            else
            {
                if (this.login)
                {
                    if (this.UsernameTxt.Text == "" || this.PasswordTxt.Text == "")
                    {
                        this.errorLbl.Visibility = Visibility.Visible;
                        this.errorLbl.Text = "Please fill in all fields";
                    }
                    else
                    {
                        //login handling
                        requestStructs.LoginRequest loginRequest = new requestStructs.LoginRequest();
                        loginRequest.username = this.UsernameTxt.Text;
                        loginRequest.password = this.PasswordTxt.Text;
                        string json = JsonConvert.SerializeObject(loginRequest);
                        byte[] data = Encoding.ASCII.GetBytes(json);
                        comm.Send(1, data);
                        Tuple<int, byte[]> response = comm.Recieve();
                        if (response.Item1 == 3)
                        {
                            responseStructs.ErrorResponse errResponse =
                                JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(
                                    Encoding.ASCII.GetString(response.Item2));
                            this.errorLbl.Visibility = Visibility.Visible;
                            this.errorLbl.Text = errResponse.message;
                        }

                        if (response.Item1 == 1)
                        {
                            //login success
                            this.errorLbl.Visibility = Visibility.Hidden;
                            this.UsernamePanel.Visibility = Visibility.Hidden;
                            this.PasswordPanel.Visibility = Visibility.Hidden;
                            this.EmailPanel.Visibility = Visibility.Hidden;
                            this.UsernameTxt.Text = "";
                            this.PasswordTxt.Text = "";
                            this.EmailTxt.Text = "";
                            this.comm.signoutFlag = true;
                            MenuWindow menu = new MenuWindow(this.comm);
                            this.Close();
                            menu.Show();
                        }
                        else
                        {
                            //login failed
                            this.errorLbl.Visibility = Visibility.Visible;
                            this.errorLbl.Text = "Login failed";
                        }
                    }
                }
                else
                {
                    if (this.UsernameTxt.Text == "" || this.PasswordTxt.Text == "" || this.EmailTxt.Text == "")
                    {
                        this.errorLbl.Visibility = Visibility.Visible;
                        this.errorLbl.Text = "Please fill in all fields";
                    }
                    else
                    {
                        //signup handling
                        requestStructs.SignUpRequest signUpRequest = new requestStructs.SignUpRequest();
                        signUpRequest.username = this.UsernameTxt.Text;
                        signUpRequest.password = this.PasswordTxt.Text;
                        signUpRequest.email = this.EmailTxt.Text;
                        string json = JsonConvert.SerializeObject(signUpRequest);
                        byte[] data = Encoding.ASCII.GetBytes(json);
                        comm.Send(2, data);
                        Tuple<int, byte[]> response = comm.Recieve();
                        if (response.Item1 == 3)
                        {
                            responseStructs.ErrorResponse errResponse =
                                JsonConvert.DeserializeObject<responseStructs.ErrorResponse>(
                                    Encoding.ASCII.GetString(response.Item2));
                            this.errorLbl.Visibility = Visibility.Visible;
                            this.errorLbl.Text = errResponse.message;
                        }
                        else if (response.Item1 == 2)
                        {
                            //signup success
                            this.errorLbl.Visibility = Visibility.Hidden;
                            this.UsernamePanel.Visibility = Visibility.Hidden;
                            this.PasswordPanel.Visibility = Visibility.Hidden;
                            this.EmailPanel.Visibility = Visibility.Hidden;
                            this.UsernameTxt.Text = "";
                            this.PasswordTxt.Text = "";
                            this.EmailTxt.Text = "";

                            this.comm.signoutFlag = true;
                            MenuWindow menu = new MenuWindow(this.comm);
                            this.Close();
                            menu.Show();
                        }
                        else
                        {
                            //signup failed
                            this.errorLbl.Visibility = Visibility.Visible;
                            this.errorLbl.Text = "Signup failed";
                        }
                    }
                }
            }
        }


        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
            this.comm.Disconnect();
            e.Cancel = false;
        }



        private void Secret_OnClick(object sender, RoutedEventArgs e)
        {
            var uri = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
            var psi = new System.Diagnostics.ProcessStartInfo("cmd", "/c start " + uri);
            System.Diagnostics.Process.Start(psi);
        }
    }
}    