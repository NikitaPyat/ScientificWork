using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Globalization;
using System.Windows;

namespace Wpf_Chart
{
    // Формат записи данных.
    // Первая строка определяет региональный стандарт (строка "en" или "ru")
    // Дальше любое число строк с описанием данных (до строки "###")
    // Следующая строка - надпись на графике по оси Ox
    // Следующая строка - надпись на графике по оси Oy
    // Следующая строка - целое число (число точек nX по оси Ox)
    // Следующие nX строк - x-координаты точек (double)
    // Следующие строки - блоки по (nX + 1) строк
    // В блоке первая строка - legend для соответствующей кривой на графике
    // Затем nX строк с у-координатами точек (double) для соответствующей кривой на графике
    // Число блоков не более 7 (длина массива с цветами в ChartView)
    class ChartData
    {
        public string filename { get; set; }
        public List<string> dataInfo { get; set; } // Информация о параметрах; до строки-разделителя "###"
        public string xTitle { get; set; } // надпись по оси Ox
        public string yTitle { get; set; } // надпись по оси Oy
        public int nX { get; set; } // число абсцисс
        public double[] X { get; set; } // значения абсцисс - отдельная строка для каждого элемента
                                        // число строк nX
        public List<double[]> YC { get; set; } // значения ординат - отдельная строка для каждой ординаты
                                               // число строк для одного векторного элемента nX; 
                                               // в файле перед строками со значениями ординат для векторного элемента - строка legend
                                             
        public List<string> legends { get; set; } // Legends (число строк nYC) 

        public ChartData(string filename)
        {
            this.filename = filename;
            dataInfo = new List<string>();
            legends = new List<string>();
            YC = new List<double[]>();
            Parse();
        }
        bool Parse()
        {
            CultureInfo.CurrentCulture = new CultureInfo("ru-RU");
            FileStream fileStream = null;
            
            string curr = "";
            try
            {
                fileStream = File.OpenRead(filename);
                using (StreamReader reader = new StreamReader(fileStream))
                {
                    string culture_string = reader.ReadLine();
                    if (culture_string == "ru") CultureInfo.CurrentCulture = new CultureInfo("ru-RU");
                    else if (culture_string == "en") CultureInfo.CurrentCulture = new CultureInfo("en-US");
                    else
                    {   MessageBox.Show($"В файле {filename} неправильная \nстрока регионального формата.\nПервая строка файла \"{culture_string}\"");
                        return false;
                    }
                    while ((curr = reader.ReadLine()) != "###") // header
                    {
                        dataInfo.Add(curr);
                    }
                    xTitle = reader.ReadLine(); // текст оси Ox
                    yTitle = reader.ReadLine(); // текст по оси Oy
                    nX = Convert.ToInt32(reader.ReadLine()); // число точек по оси Ox

                    X = new double[nX];
                    for (int j = 0; j < nX; j++)
                    {
                        X[j] = Convert.ToDouble(reader.ReadLine());
                    }
                    while ((curr = reader.ReadLine()) != null) 
                    {
                        legends.Add(curr);

                        double[] Y = new double[nX];
                        for (int j = 0; j < nX; j++)
                        {
                            Y[j] = Convert.ToDouble(reader.ReadLine());
                        }
                        YC.Add(Y);
                    }
                }
                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error ChartData.Parse\n " + ex.Message);
                return false;
            }
            finally
            {
                if (fileStream != null)
                {
                    fileStream.Close();
                }
            }
        }
    }
}
