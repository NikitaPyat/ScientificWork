// Test_complex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <complex>
#include <fstream>
#include "U1.h"
#include "AndersonCPP/AndersonCPP/HankelTransformsByAnderson.h"

using namespace std;

U1 func = U1();

void fComplex(double x, int fv_length, complex<double>* fv)
{
    for (int j = 0; j < fv_length; j++)
    {
        fv[j] = func.getU1(x);
    }

}

int main()
{

    double eps = 0.1;
    const int j0_cn = 1;
    const int j1_cn = 1;

    complex<double> cres[j0_cn + j1_cn];
    complex<double> cc[j0_cn + j1_cn];
    complex<double> ccmax[j0_cn + j1_cn];

    const int nr = 9;
    const double r[nr]{ 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09 };
    for (int j = 0; j < nr; j++)
    {
        std::cout << "\nr = " << r[j] << std::endl;

        HankelTransformsByAnderson hta;
        hta.callComplex(fComplex, r[j], eps, j0_cn, j1_cn, cres, cc, ccmax);

        for (int jf = 0; jf < j0_cn; jf++)
            std::cout << " value from Anderson J0 = " << cres[jf] << std::endl;
        for (int jf = 0; jf < j1_cn; jf++)
            std::cout << " value from Anderson J1 = " << cres[jf + j0_cn] << std::endl;
    }
}