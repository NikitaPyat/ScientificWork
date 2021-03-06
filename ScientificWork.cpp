// Test_complex.cpp : ???? ???? ???????? ??????? "main". ????? ?????????? ? ????????????? ?????????? ?????????.
//

#include <iostream>
#include <complex>
#include <fstream>
#include "U1.h"
#include "AndersonCPP/AndersonCPP/HankelTransformsByAnderson.h"

using namespace std;

void fComplex(double x, int fv_length, complex<double>* fv)
{
    U1 func = U1(x);
    for (int j = 0; j < fv_length; j++)
    {
        fv[j] = func.getU1();
        //cout << fv[j] << "; j = " << j << '\n';
    }

}

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "?????? ???!\n";

    double eps = 0.0001;
    const int j0_cn = 1;
    const int j1_cn = 1;
    complex<double> cres[j0_cn + j1_cn];
    complex<double> cc[j0_cn + j1_cn];
    complex<double> ccmax[j0_cn + j1_cn];

    const int nr = 3;
    const double r[nr]{ 0.1, 0.2, 0.3 };

    //ofstream fout("Ax.txt"); // ??????? ?????? ?????? ofstream ??? ?????? ? ????????? ??? ? ?????? cppstudio.txt
    //fout.open("test.txt", std::ofstream::out | std::ofstream::trunc); // ??????? ?????
    //fout << "en\n";
    //fout << "Parameters\n";
    //fout << "eps1 = 2*eps0\n";
    //fout << "eps2 = 6*eps0\n";
    //fout << "h = pi / sqrt(eps0 * mu)\n";
    //fout << "###\n";
    //fout << "lambda\n";
    //fout << "Ax(J0)\n";
    //fout << "9\n";
    //for (double lambda = 1; lambda < 10; lambda += 1) {
    //    fout << lambda;
    //    fout << "\n";
    //}
    //fout << "U\n";
    for (int j = 0; j < nr; j++)
    {
        std::cout << "\nr = " << r[j] << std::endl;

        HankelTransformsByAnderson hta;
        hta.callComplex(fComplex, r[j], eps, j0_cn, j1_cn, cres, cc, ccmax);

        for (int jf = 0; jf < j0_cn; jf++)
            std::cout << " value from Anderson J0 = " << cres[jf] << std::endl;
        for (int jf = 0; jf < j1_cn; jf++)
            std::cout << " value from Anderson J1 = " << cres[jf + j0_cn] << std::endl;


        /*fout << res[0];
        fout << "\n";
        std::cout << " value from Anderson J0  = " << res[0] << std::endl;
        std::cout << " value from Anderson J1 = " << res[1] << std::endl;*/
    }
    //for (double lambda = 1; lambda < 10; lambda += 1) {
    //    Model_2L& model = *(new Model_2L(lambda));
    //    fout << model.dUdeps1().real() * 1.0E+16; // ?????? ?????? ? ????
    //    fout << "\n";
    //    std::cout << "dU/deps1 : " << model.dUdeps1().real() * 1.0E+16 << std::endl;
    //}

    //fout << "W\n";
    //for (double lambda = 1; lambda < 10; lambda += 1) {
    //    Model_2L& model = *(new Model_2L(lambda));
    //    fout << model.dWdeps1().real() * 1.0E+16; // ?????? ?????? ? ????
    //    fout << "\n";
    //    std::cout << "dU/deps1 : " << model.dWdeps1().real() * 1.0E+16 << std::endl;
    //}
    //fout.close(); // ????????? ????

    /*std::cout << "dU/deps1 : " << model.dUdeps1() << std::endl;
    std::cout << "dU/deps2 : " << model.dUdeps2() << std::endl;
    std::cout << "dU/dh : " << model.dUdh() << std::endl;

    std::cout << "dW/deps1 : " << model.dWdeps1() << std::endl;
    std::cout << "dW/deps2 : " << model.dWdeps2() << std::endl;
    std::cout << "dW/dh : " << model.dWdh() << std::endl;*/
}