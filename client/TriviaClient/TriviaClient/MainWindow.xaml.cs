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
            UsernamePanel.Visibility = Visibility.Hidden;
            PasswordPanel.Visibility = Visibility.Hidden;
            EmailPanel.Visibility = Visibility.Hidden;
        }

        private void LogInBtn_Click(object sender, RoutedEventArgs e)
        {
            this.login = true;
            UsernamePanel.Visibility = Visibility.Visible;
            PasswordPanel.Visibility = Visibility.Visible;
            EmailPanel.Visibility = Visibility.Hidden;


        }

        private void SignUpBtn_Click(object sender, RoutedEventArgs e)
        {
            this.login = false;
            UsernamePanel.Visibility = Visibility.Visible;
            PasswordPanel.Visibility = Visibility.Visible;
            EmailPanel.Visibility = Visibility.Visible;

        }

        private void SubmitBtn_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
