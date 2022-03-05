#pragma once
#include <iostream>
#include <complex>
#include <math.h>

using namespace std;
class U1
{
	const double mu = 4 * 3.14159 * 1.0E-7;
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
	U1() {
		this->eps1 = 2 * eps0;
		this->eps2 = 6 * eps0;

		this->z0 = 5 * 1.0E-7;
		this->z = 5 * 1.0E-8;
		this->w = 1;

		k0k0 = w * w * eps0 * mu;
		k1k1 = w * w * eps1 * mu;
		k2k2 = w * w * eps2 * mu;
	}

	complex<double> getU1(double lambda) {

		double lambda0 = 2 * 3.14159 / sqrt(eps0 * mu);
		this->h = lambda0 / 2;
		this->lambda = lambda;

		nu0 = sqrt(lambda * lambda - k0k0);
		nu1 = sqrt(lambda * lambda - k1k1);
		nu2 = sqrt(lambda * lambda - k2k2);
		nu12 = (nu1 - nu2) / (nu1 + nu2);
		nu01 = (nu0 - nu1) / (nu0 + nu1);
		R1 = nu12 * exp(-2 * nu1.real() * h);
		R0 = (R1 + nu01) / (R1.real() * nu01.real() + 1);

		a0 = R0 * mu * exp(-nu0 * z0) / nu0 - mu * exp(nu0 * z0) / nu0;
		b0 = mu * exp(-nu0 * z0) / nu0;

		return a0 * exp(-sqrt(lambda * lambda - k0k0) * z) + b0 * exp(sqrt(lambda * lambda - k0k0) * z);
	}
};