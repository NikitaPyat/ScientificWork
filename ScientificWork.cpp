#include <iostream>

struct Specifications {
    int E0;
    int E1;
    int E2;
    int w;
    int mu;
    int h;
    int Z0;
    int lambda;
    int omega;
};

Specifications sp = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

int eta0 = sqrt(sp.lambda ^ 2 - sp.omega ^ 2 * sp.E0 * sp.mu);
int eta1 = sqrt(sp.lambda ^ 2 - sp.omega ^ 2 * sp.E1 * sp.mu);
int eta2 = sqrt(sp.lambda ^ 2 - sp.omega ^ 2 * sp.E2 * sp.mu);

double eta01() {
    return (eta0 - eta1) / (eta0 + eta1);
}

double eta12() {
    return (eta1 - eta2) / (eta1 + eta2);
}

int main() {
    int R1 = eta01() * exp(-2 * eta1 * sp.h);
    int R0 = (R1 + eta01()) / (R1 * eta01() + 1);
}