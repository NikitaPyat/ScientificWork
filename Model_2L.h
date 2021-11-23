#pragma once
#include <iostream>
#include <complex>
#include <math.h>
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
	double omega0110;
	double omega0121;
	double omega1221;
	double F0;
	double F1;

public:
	Model_2L(double lambda)
	{
		this->eps1 = 2*eps0;
		this->eps2 = 6*eps0;

		double lambda0 = 2 * 3.14159 / sqrt(eps0 * mu);
		this->h = lambda0 / 2;
		this->z0 = 5 * 1.0E-7;
		this->z = 0;
		this->w = 1;
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
		omega0110 = (k1k1 * nu0 - k0k0 * nu1) / (k1k1 * nu0 + k0k0 * nu1);
		omega0121 = (k2k2 * nu0 - k0k0 * nu1) / (k1k1 * nu0 + k0k0 * nu1);
		omega1221 = (k2k2 * nu1 - k1k1 * nu2) / (k2k2 * nu1 + k1k1 * nu2);
		F1 = omega1221 * exp(-2 * nu1 * h);
		F0 = (F1 + omega0110) / (F1 * omega0110 + 1);
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

	void Uoutput()
	{
		std::cout << "Модель:" << std::endl;
		std::cout << "eps0 = " << eps0 << "  eps1 = " << eps1 << "  eps2 = " << eps2 << std::endl;
		std::cout << "h = " << h << "  z0 = " << z0 << "  z = " << z << std::endl;
	}









	std::complex<double> dWdeps1() {
		return dF0deps1() * R0 * mu * exp(-nu0 * (z + z0)) + dR0deps1() * F0 * mu * exp(-nu0 * (z + z0));
	}

	std::complex<double> dWdeps2() {
		return dF0deps2() * R0 * mu * exp(-nu0 * (z + z0)) + dR0deps2() * F0 * mu * exp(-nu0 * (z + z0));
	}
	std::complex<double> dWdh() {
		return dF0dh() * R0 * mu * exp(-nu0 * (z + z0)) + dR0dh() * F0 * mu * exp(-nu0 * (z + z0));
	}


	std::complex<double> dF0deps1() {
		return (dF1deps1() + dk10nu01deps1()) / (F1 * omega0121 + 1) - (F1 + omega0110) * (dF1deps1() * omega0110 + F1 * dk10nu01deps1()) / ((F1 * omega0121 + 1) * (F1 * omega0121 + 1));
	}

	std::complex<double> dF0deps2() {
		return (dF1deps2() + dk10nu01deps2()) / (F1 * omega0121 + 1) - (F1 + omega0110) * (dF1deps2() * omega0110 + F1 * dk10nu01deps2()) / ((F1 * omega0121 + 1) * (F1 * omega0121 + 1));
	}

	std::complex<double> dF0dh() {
		return dF1dh() / (F1 * omega0121 + 1) - (F1 + omega0110) * dF1dh() * omega0110 / ((F1 * omega0121 + 1) * (F1 * omega0121 + 1));
	}


	std::complex<double> dF1deps1() {
		return dk10nu12deps1() * exp(-2 * nu1 * h) + h * R1 * w * w * mu / nu1;
	}

	std::complex<double> dF1deps2() {
		return dk10nu12deps2() * exp(-2 * nu1 * h);
	}

	std::complex<double> dF1dh() {
		return -2 * h * F1;
	}


	std::complex<double> dk10nu01deps1() {
		return k1k1 * w * w * mu / (2 * nu1 * (k0k0 * nu1 + k1k1 * nu0)) - (k1k1 * nu0 - k0k0 * nu1) * w * w * mu / (2 * nu1 * (k0k0 * nu1 + k1k1 * nu0) * (k0k0 * nu1 + k1k1 * nu0));
	}

	std::complex<double> dk10nu01deps2() {
		return 0;
	}

	std::complex<double> dk10nu12deps1() {
		return k2k2 * w * w * mu / (2 * nu1 * (k2k2 * nu1 + k1k1 * nu2)) - (k2k2 * nu1 - k1k1 * nu2) * w * w * mu / (2 * nu1 * (k2k2 * nu1 + k1k1 * nu2) * (k2k2 * nu1 + k1k1 * nu2));
	}

	std::complex<double> dk10nu12deps2() {
		return k1k1 * w * w * mu / (2 * nu2 * (k2k2 * nu1 + k1k1 * nu2)) - (k2k2 * nu1 - k1k1 * nu2)  * w * w * mu / (2 * nu2 * (k2k2 * nu1 + k1k1 * nu2) * (k2k2 * nu1 + k1k1 * nu2));
	}
};
