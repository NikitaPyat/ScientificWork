#pragma once
#include <iostream>
#include <complex>
#include <math.h>
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
	double nu0;
	double nu1;
	double nu2;
	double nu12;
	double nu01;
	double R0;
	double R1;

	double a0;
	double b0;

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

	double getU1(double lambda) {

		double lambda0 = 2 * 3.14159 / sqrt(eps0 * mu);
		this->h = lambda0 / 2;
		this->lambda = lambda;

		nu0 = sqrt(lambda * lambda - k0k0);
		nu1 = sqrt(lambda * lambda - k1k1);
		nu2 = sqrt(lambda * lambda - k2k2);
		nu12 = (nu1 - nu2) / (nu1 + nu2);
		nu01 = (nu0 - nu1) / (nu0 + nu1);
		R1 = nu12 * exp(-2 * nu1 * h);
		R0 = (R1 + nu01) / (R1 * nu01 + 1);

		a0 = R0 * mu * exp(-nu0 * z0) / nu0 - mu * exp(nu0 * z0) / nu0;
		b0 = mu * exp(-nu0 * z0) / nu0;

		return a0 * exp(-sqrt(lambda * lambda - k0k0) * z) + b0 * exp(sqrt(lambda * lambda - k0k0) * z);
	}
};