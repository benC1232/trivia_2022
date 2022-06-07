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
    /// Interaction logic for PostGameWindow.xaml
    /// </summary>
    public partial class PostGameWindow : Window
    {
        private DispatcherTimer timer;
        private Communicator comm;

        public PostGameWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
            this.timer = new DispatcherTimer();
            this.timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += timer_Tick;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            this.countdown.Content = 30 - DateTime.Now.Second;
            if (DateTime.Now.Second == 30)
            {
                //leave
            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
        }
    }
}