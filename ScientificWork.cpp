// Test_complex.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include <iostream>
#include <complex>
#include <fstream>
#include "Model_2L.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "������ ���!\n";

    ofstream fout("dU/deps1.txt"); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ cppstudio.txt
    fout.open("test.txt", std::ofstream::out | std::ofstream::trunc); // ������� �����
    fout << "en\n";
    fout << "Parameters\n";
    fout << "eps1 = 2*eps0\n";
    fout << "eps2 = 6*eps0\n";
    fout << "h = pi / sqrt(eps0 * mu)\n";
    fout << "###\n";
    fout << "lambda\n";
    fout << "d/deps1 * 1.0E+16\n";
    fout << "9\n";
    for (double lambda = 1; lambda < 10; lambda += 1) {
        fout << lambda;
        fout << "\n";
    }
    fout << "U\n";
    for (double lambda = 1; lambda < 10; lambda += 1) {
        Model_2L& model = *(new Model_2L(lambda));
        fout << model.dUdeps1().real() * 1.0E+16; // ������ ������ � ����
        fout << "\n";
        std::cout << "dU/deps1 : " << model.dUdeps1().real() * 1.0E+16 << std::endl;
    }

    fout << "W\n";
    for (double lambda = 1; lambda < 10; lambda += 1) {
        Model_2L& model = *(new Model_2L(lambda));
        fout << model.dWdeps1().real() * 1.0E+16; // ������ ������ � ����
        fout << "\n";
        std::cout << "dU/deps1 : " << model.dWdeps1().real() * 1.0E+16 << std::endl;
    }
    fout.close(); // ��������� ����

    /*std::cout << "dU/deps1 : " << model.dUdeps1() << std::endl;
    std::cout << "dU/deps2 : " << model.dUdeps2() << std::endl;
    std::cout << "dU/dh : " << model.dUdh() << std::endl;

    std::cout << "dW/deps1 : " << model.dWdeps1() << std::endl;
    std::cout << "dW/deps2 : " << model.dWdeps2() << std::endl;
    std::cout << "dW/dh : " << model.dWdh() << std::endl;*/
}