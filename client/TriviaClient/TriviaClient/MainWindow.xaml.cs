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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool login;

        public MainWindow()
        {
            InitializeComponent();
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
            if (this.login)
            {
                if (this.UsernameTxt.Text == "" || this.PasswordTxt.Text == "")
                {
                    this.errorLbl.Visibility = Visibility.Visible;
                    this.errorLbl.Text = "Please fill in all fields";
                }
                else
                {
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
                    MenuWindow menu = new MenuWindow();
                    this.Close();
                    menu.ShowDialog();
                }
            }
        }
    }
}