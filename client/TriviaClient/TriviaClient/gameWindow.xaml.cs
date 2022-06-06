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
        private DispatcherTimer timer;
        private int TotalSeconds;
        public gameWindow()
        {
            InitializeComponent();

            this.timer = new DispatcherTimer();
            this.timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += timer_Tick;
            //remember to start the timer

        }

        void timer_Tick(object sender, EventArgs e)
        {
            this.countdown.Content = TotalSeconds - DateTime.Now.Second;
            if (TotalSeconds - DateTime.Now.Second == 0)
            {
                //------------
            }
            
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            e.Cancel = true;
        }

        private void Answer1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer2_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer3_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Answer4_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
