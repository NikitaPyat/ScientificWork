#pragma once
#include <iostream>
#include <complex>
class Model_2L
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

public:
	Model_2L(double eps1, double eps2, double h, double z0, double w, double z, double lambda)
	{
		this->eps1 = eps1;
		this->eps2 = eps2;
		this->h = h;
		this->z0 = z0;
		this->z = z;
		this->w = w;
		this->lambda = lambda;

		k0k0 = w * w * eps0 * mu;
		k1k1 = w * w * eps1 * mu;
		k2k2 = w * w * eps2 * mu;
		nu0 = sqrt(lambda * lambda - k0k0);
		nu1 = sqrt(lambda * lambda - k1k1);
		nu2 = sqrt(lambda * lambda - k2k2);
		nu12 = (nu1 - nu2) / (nu1 + nu2);
		nu01 = (nu0 - nu1) / (nu0 + nu1);
		R1 = nu12 * exp(-2 * nu1 * h);
		R0 = (R1 + nu01) / (R1 * nu01 + 1);
	}

	std::complex<double> dUdeps1() {
		return dR0deps1() * mu * exp(-nu0 * (z + z0)) / nu0;
	}

	std::complex<double> dUdeps2() {
		return dR0deps2() * mu * exp(-nu0 * (z + z0)) / nu0;
	}
	std::complex<double> dUdh() {
		return dR0dh() * mu * exp(-nu0 * (z + z0)) / nu0;
	}


	std::complex<double> dR0deps1() {
		return (dR1deps1() + dnu01deps1()) / (R1 * nu01 + 1) - (R1 + nu01)*(dR1deps1()*nu01 + R1 * dnu01deps1()) / ((R1*nu01 + 1) * (R1 * nu01 + 1));
	}

	std::complex<double> dR0deps2() {
		return (dR1deps2() + dnu01deps2()) / (R1 * nu01 + 1) - (R1 + nu01) * (dR1deps2() * nu01 + R1 * dnu01deps2()) / ((R1 * nu01 + 1) * (R1 * nu01 + 1));
	}

	std::complex<double> dR0dh() {
		return dR1dh() / (R1 * nu01 + 1) - (R1 + nu01) * dR1dh() * nu01 / ((R1 * nu01 + 1) * (R1 * nu01 + 1));
	}


	std::complex<double> dR1deps1() {
		return dnu12deps1() * exp(-2*nu1*h) + h*R1*w*w*mu/nu1;
	}

	std::complex<double> dR1deps2() {
		return dnu12deps2() * exp(-2 * nu1 * h);
	}

	std::complex<double> dR1dh() {
		return -2 * h * R1;
	}


	std::complex<double> dnu01deps1() {
		return (nu0/nu1) * w * w * mu / ((nu1 + nu0) * (nu1 + nu0));
	}

	std::complex<double> dnu01deps2() {
		return 0;
	}

	std::complex<double> dnu12deps1() {
		return -(nu2 / nu1) * w * w * mu / ((nu1 + nu0) * (nu1 + nu0));
	}

	std::complex<double> dnu12deps2() {
		return (nu1 / nu2) * w * w * mu / ((nu1 + nu0) * (nu1 + nu0));
	}

	void output()
	{
		std::cout << "Модель:" << std::endl;
		std::cout << "eps0 = " << eps0 << "  eps1 = " << eps1 << "  eps2 = " << eps2 << std::endl;
		std::cout << "h = " << h << "  z0 = " << z0 << "  z = " << z << std::endl;
	}
};
