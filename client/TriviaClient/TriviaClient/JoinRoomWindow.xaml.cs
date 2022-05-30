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
using Newtonsoft.Json;

namespace TriviaClient
{
    /// <summary>
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {
        public JoinRoomWindow()
        {
            List<String> items = new List<String>();
            items.Add("Room 1");
            items.Add("Room 2");
            items.Add("Room 3");

            this.roomsListLstBx.ItemsSource = items;
            InitializeComponent();
        }

        private void JoinRoomBtn_Click(object sender, RoutedEventArgs e)
        {
            String selectedRoomName = this.roomsListLstBx.SelectedItem.ToString();
        }

        private void roomsListLstBx_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            this.JoinRoomBtn.Content = "Join " + this.roomsListLstBx.SelectedItem.ToString();
        }
    }
}