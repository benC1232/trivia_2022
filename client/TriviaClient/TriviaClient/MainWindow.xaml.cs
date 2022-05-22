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

            this.UsernamePanel.Visibility = Visibility.Hidden;
            this.PasswordPanel.Visibility = Visibility.Hidden;
            this.EmailPanel.Visibility = Visibility.Hidden;
            this.errorLbl.Visibility = Visibility.Hidden;
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
            if (!comm.connected)
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
                        MenuWindow menu = new MenuWindow();
                        this.Close();
                        menu.ShowDialog();
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

                        MenuWindow menu = new MenuWindow();
                        this.Close();
                        menu.ShowDialog();
                    }
                }
            }
        }
    }
}