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
    /// Interaction logic for waitingRoom.xaml
    /// </summary>
    public partial class waitingRoom : Window
    {
        private Communicator comm;
        private DispatcherTimer timer;

        public waitingRoom(Communicator c)
        {
            this.comm = c;
            //💻 - paste it before the admin username
            InitializeComponent();
            this.errorLbl.Visibility = Visibility.Hidden;
            refresh();
            timer = new System.Windows.Threading.DispatcherTimer();
            timer.Tick += new EventHandler(dispatcherTimer_Tick);
            timer.Interval = new TimeSpan(0, 0, 3);
            timer.Start();
        }

        

        private void refresh()
        {
            //BackSide:
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            refresh();
        }

    }
}
