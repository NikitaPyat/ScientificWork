#pragma once
#include <iostream>
#include <complex>
#include <math.h>
using namespace std;
class U1
{
	const double mu0 = 4 * 3.14159 * 1.0E-7;
	const double mu = 1.55;
	const double eps0 = 8.8541878e-12;

private:
	double eps1;
	double eps2;
	double h;
	double z0;
	double w;
	double z;
	double lambda;
	double k0k0;
	double k1k1;
	double k2k2;

	complex<double> nu0;
	complex<double> nu1;
	complex<double> nu2;
	complex<double> nu12;
	complex<double> nu01;
	complex<double> R0;
	complex<double> R1;
	complex<double> a0;
	complex<double> b0;

public:
	U1(double lambda)
	{
		this->eps1 = 2 * eps0;
		this->eps2 = 6 * eps0;

		this->w = 1;
		long double lambda0 = 2 * 3.14159 / (w * sqrt(eps0 * mu0));
		this->h = lambda0 / 2;
		this->z0 = 5 * 1.0E-10;
		this->z = 0;
		this->lambda = lambda;

		this->k0k0 = w * w * eps0 * mu0;
		this->k1k1 = w * w * eps1 * mu;
		this->k2k2 = w * w * eps2 * mu;
		this->nu0 = sqrt(complex<double>(lambda * lambda - k0k0, 0));
		this->nu1 = sqrt(complex<double>(lambda * lambda - k1k1, 0));
		this->nu2 = sqrt(complex<double>(lambda * lambda - k2k2, 0));
		this->nu12 = (nu1 - nu2) / (nu1 + nu2);
		this->nu01 = (nu0 - nu1) / (nu0 + nu1);
		this->R1 = nu12 * exp(complex<double>(-2, 0) * nu1 * h);
		this->R0 = (R1 + nu01) / ((R1 * nu01) + 1.0);

		this->a0 = R0 * mu * exp(-nu0 * z0) / nu0;
		this->b0 = mu * exp(-nu0 * z0) / nu0;
	}

	complex<double> getU1() {
		complex<double> out = a0 * exp(-sqrt(lambda * lambda - k0k0) * z) + b0 * exp(sqrt(lambda * lambda - k0k0) * z);
		cout << nu1 << " " << out << endl;
		return a0 * exp(-sqrt(lambda * lambda - k0k0) * z) + b0 * exp(sqrt(lambda * lambda - k0k0) * z);
	}
};