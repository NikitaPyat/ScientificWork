// Test_complex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <complex>
#include <fstream>
#include "U1.h"
#include "AndersonCPP/AndersonCPP/HankelTransformsByAnderson.h"

using namespace std;

U1 func = U1();

void f_U1(double x, int fv_length, double* fv)
{
    for (int j = 0; j < fv_length; j++)
    {
        fv[j] = func.getU1(x);
        //cout << fv[j] << "; j = " << j << "\n";
    }

}

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Привет мир!\n";

    double eps = 0.00001;
    int j0_n = 1;
    int j1_n = 1;
    double res[2];
    double c[2];
    double cmax[2];

    const int nr = 9;
    const double r[nr]{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };

    ofstream fout("Ax.txt"); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
    fout.open("test.txt", std::ofstream::out | std::ofstream::trunc); // очистка файла
    fout << "en\n";
    fout << "Parameters\n";
    fout << "eps1 = 2*eps0\n";
    fout << "eps2 = 6*eps0\n";
    fout << "h = pi / sqrt(eps0 * mu)\n";
    fout << "###\n";
    fout << "lambda\n";
    fout << "Ax(J0)\n";
    fout << "9\n";
    for (double lambda = 1; lambda < 10; lambda += 1) {
        fout << lambda;
        fout << "\n";
    }
    fout << "U\n";
    for (int j = 0; j < nr; j++)
    {
        std::cout << "\nr = " << r[j] << std::endl;

        HankelTransformsByAnderson hta;
        hta.call(f_U1, r[j], eps, j0_n, j1_n, res, c, cmax);
        fout << res[0];
        fout << "\n";
        std::cout << " value from Anderson J0  = " << res[0] << std::endl;
        std::cout << " value from Anderson J1 = " << res[1] << std::endl;
    }
    //for (double lambda = 1; lambda < 10; lambda += 1) {
    //    Model_2L& model = *(new Model_2L(lambda));
    //    fout << model.dUdeps1().real() * 1.0E+16; // запись строки в файл
    //    fout << "\n";
    //    std::cout << "dU/deps1 : " << model.dUdeps1().real() * 1.0E+16 << std::endl;
    //}

    //fout << "W\n";
    //for (double lambda = 1; lambda < 10; lambda += 1) {
    //    Model_2L& model = *(new Model_2L(lambda));
    //    fout << model.dWdeps1().real() * 1.0E+16; // запись строки в файл
    //    fout << "\n";
    //    std::cout << "dU/deps1 : " << model.dWdeps1().real() * 1.0E+16 << std::endl;
    //}
    fout.close(); // закрываем файл

    /*std::cout << "dU/deps1 : " << model.dUdeps1() << std::endl;
    std::cout << "dU/deps2 : " << model.dUdeps2() << std::endl;
    std::cout << "dU/dh : " << model.dUdh() << std::endl;

    std::cout << "dW/deps1 : " << model.dWdeps1() << std::endl;
    std::cout << "dW/deps2 : " << model.dWdeps2() << std::endl;
    std::cout << "dW/dh : " << model.dWdh() << std::endl;*/
}