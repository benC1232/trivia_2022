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

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for About.xaml
    /// </summary>
    public partial class About : Window
    {
        private Communicator comm;
        public About(Communicator c)
        {
            InitializeComponent();
            this.comm = c;
        }

        private void BackToMenuBtn_OnClick(object sender, RoutedEventArgs e)
        {
            MainWindow main = new MainWindow(comm);
            this.Close();
            main.Show();
        }
    }
}
