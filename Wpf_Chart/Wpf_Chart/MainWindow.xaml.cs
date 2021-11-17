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
using Microsoft.Win32;
using System.Windows.Forms.DataVisualization.Charting;

namespace Wpf_Chart
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Chart chart_Top =  new Chart();
        Chart chart_Bottom = new Chart();
        //ChartData chartData_Top;
        //ChartData chartData_Bottom;
        public MainWindow()
        {
            InitializeComponent();
           
            winFormsHost_Top.Child = chart_Top;
            winFormsHost_Bottom.Child = chart_Bottom;
            //grid_Top.DataContext = chartData_Top;
            //grid_Bottom.DataContext = chartData_Bottom;
        }

        private void button_Top_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();

            if (dlg.ShowDialog() == true)
            {
                textBlock_Top.Text = "Данные из файла:  " + dlg.FileName;
                try
                {
                    ChartData chartData_Top = new ChartData(dlg.FileName);
                    listBox_Top.ItemsSource = chartData_Top.dataInfo;
                    ChartView.Draw(chart_Top, chartData_Top);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Error in button_Top_Click\n" + ex.Message);
                }
            }
        }

        private void button_Bottom_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();

            if (dlg.ShowDialog() == true)
            {
                textBlock_Bottom.Text = "Данные из файла:  " + dlg.FileName;
                try
                {
                    ChartData chartData_Bottom = new ChartData(dlg.FileName);
                    listBox_Bottom.ItemsSource = chartData_Bottom.dataInfo;
                    ChartView.Draw(chart_Bottom, chartData_Bottom);
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Error in button_Top_Click\n" + ex.Message);
                }
            }
        }
        //private void SelectFile_and_Draw(object sender)
        //{
        //    ChartData chartData;
        //    Chart chart;
        //    TextBlock textBlock;
        //    if((string)(sender as FrameworkElement).Tag =="Top")
        //    {
        //        chartData = chartData_Top;
        //        chart = chart_Top;
        //        textBlock = textBlock_Top;
        //    }
        //    else
        //    {
        //        chartData = chartData_Bottom;
        //        chart = chart_Bottom;
        //        textBlock = textBlock_Bottom;
        //    }

        //    OpenFileDialog dlg = new OpenFileDialog();

        //    if (dlg.ShowDialog() == true)
        //    {
        //        textBlock.Text = "Данные из файла:  " + dlg.FileName;
        //        try
        //        {
        //            chartData = new ChartData(dlg.FileName);
        //            ChartView.Draw(chart, chartData);
        //        }
        //        catch (Exception ex)
        //        {
        //            MessageBox.Show($"Error in SelectFile_and_Draw\n" + ex.Message);
        //        }
        //        finally
        //        {
        //        }
        //    }
        //}
    }
}
