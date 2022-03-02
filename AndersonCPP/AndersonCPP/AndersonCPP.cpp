// AndersonCPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <complex>
#include <math.h>
#include <locale.h>
#include "HankelTransformsByAnderson.h"
using namespace std;

// Функции для отладки. Для них известно преобразование Ханкеля
void f0(double x, int fv_length, double* fv)
{
    double z = 1.0;

    for (int j = 0; j < fv_length; j++)
    {
        fv[j] = exp(-z * x);
    }

}
// Преобразование Ханкеля для f0
void f0_exact(double r, double res[2]) // Тихонов, Самарский, стр. 659
{
    double z = 1.0;
    res[0] = 1.0 / sqrt(r * r + z * z);            // Ответ для J0
    res[1] = (1.0 - z / sqrt(r * r + z * z)) / r;  // Ответ для J1
}


void f1(double x, int fv_length, double* fv) // Прудников,  стр. 174
{
    for (int j = 0; j < fv_length; j++)
    {
        fv[j] = 1.0;
    }

}
// Преобразование Ханкеля для f1 (для J0)
double f1_exact(double r)
{
    return 1.0 / r;
}


void f2(double x, int fv_length, double* fv)   // Прудников, стр. 179
{
    double z = 1.0;
    for (int j = 0; j < fv_length; j++)
    {
        fv[j] = 1.0 / sqrt(z * z + x * x);
    }

}
// Преобразование Ханкеля для f2 (для J1)
double f2_exact(double r)
{
    double z = 1.0;
    return (1.0 - exp(-r * z)) / r / z;
}

// И действительная и мнимая часть равны f0
void fComplex(double x, int fv_length, complex<double>* fv)
{
    double z = 1.0;

    for (int j = 0; j < fv_length; j++)
    {
        double tmp = exp(-z * x);
        fv[j] =  complex<double> (tmp, tmp) ;
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
   
    const int nr = 4;
    const double r[nr]{ 1.0, 100.0, 1000.0, 10000.0 };

    for (int j = 0; j < nr; j++)
    {
        std::cout << "\nr = " << r[j] << std::endl;

        f0_exact(r[j], res);

        double exact_0 = res[0];
        double exact_1 = res[1];

        HankelTransformsByAnderson hta;
        hta.call(f0, r[j], eps, j0_n, j1_n, res, c, cmax);

        std::cout << "exact J0 = " << exact_0 << " value from Anderson = " << res[0] << std::endl;
        std::cout << "exact J1 = " << exact_1 << " value from Anderson = " << res[1] << std::endl;

        hta.call(f1, r[j], eps, j0_n, j1_n, res, c, cmax);
        std::cout << "\nexact J0 = " << f1_exact(r[j]) << " value from Anderson = " << res[0] << std::endl;
        //std::cout << "\nexact J1 = " << exact_1 << " value from Anderson = " << res[1] << std::endl;


        hta.call(f2, r[j], eps, j0_n, j1_n, res, c, cmax);
        //std::cout << "\nexact J0 = " << exact_0 << " value from Anderson = " << res[0] << std::endl;
        std::cout << "\nexact J1 = " << f2_exact(r[j]) << " value from Anderson = " << res[1] << std::endl;
    }

    std::cout << "\nTest complex\n" << endl;
    
    const int j0_cn = 3;
    const int j1_cn = 2;
    complex<double> cres[j0_cn + j1_cn];
    complex<double> cc[j0_cn + j1_cn];
    complex<double> ccmax[j0_cn + j1_cn];
   
    for (int j = 0; j < nr; j++)
    {
        std::cout << "\nr = " << r[j] << std::endl;

        f0_exact(r[j], res);

        double exact_0 = res[0];
        double exact_1 = res[1];

        HankelTransformsByAnderson hta;
        hta.callComplex(fComplex, r[j], eps, j0_cn, j1_cn, cres, cc, ccmax);

        for (int jf = 0; jf < j0_cn ; jf++)
        std::cout << "exact J0 = " << exact_0 << " value from Anderson = " << cres[jf] << std::endl;
        for (int jf = 0; jf < j1_cn; jf++)
        std::cout << "exact J1 = " << exact_1 << " value from Anderson = " << cres[jf + j0_cn] << std::endl;
    }
}



