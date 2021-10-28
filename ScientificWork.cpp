// Test_complex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <complex>
#include "Model_2L.h"

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Привет мир!\n";
    double eps1 = 1.0;
    double eps2 = 2.0;
    double h = 4.0;
    double z = 2;
    double z0 = 4;
    double w = 16;
    double lambda = 3;
    Model_2L& model = *(new Model_2L(eps1, eps2, h, z0, w, z, lambda));
    /*std::cout << "eps1 : " << model.dUdeps1() << std::endl;
    std::cout << "eps2 : " << model.dUdeps2() << std::endl;
    std::cout << "h : " << model.dUdh() << std::endl;*/
}