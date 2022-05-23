﻿using System;
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
    /// Interaction logic for personalStatsWindow.xaml
    /// </summary>
    public partial class personalStatsWindow : Window
    {
        private Communicator comm;

        public personalStatsWindow(Communicator c)
        {
            this.comm = c;
            InitializeComponent();
        }

        private void backToMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            MenuWindow menuWindow = new MenuWindow(this.comm);
            this.Close();
            menuWindow.Show();
        }
    }
}