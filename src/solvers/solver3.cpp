#include "computor.hpp"
#include <cmath>



void solver3(std::map<size_t, double> &polynom) {
    double a = polynom[3];
    double b = polynom[2];
    double c = polynom[1];
    double d = polynom[0];

    double p = (3 * a * c - b * b) / (3 * a * a);
    double q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);

    double delta = myPow(q / 2, 2) + myPow(p / 3, 3);

    std::cout << "\tdelta: " << delta << std::endl;

    double T1 = 0;
    Complex T2, T3;

    if (delta > 0) {
        double u = mynRoot(-q / 2 + mynRoot(delta, 2), 3);
        double v = mynRoot(-q / 2 - mynRoot(delta, 2), 3);
        T1 = u + v;
        T2 = Complex(-T1 / 2, (u - v) * mynRoot(3, 2) / 2);
        T3 = T2.conjugate();
    } else if (delta == 0) {
        if (q == 0) {
            T1 = 0;
            T2 = T3 = 0;
        } else {
            T1 = 3 * q / p;
            T2 = T3 = -3 * q / (2 * p);
        }
    } else {
        double r = mynRoot(-p / 3, 2);
        double theta = myArcCos((3 * q) / (2 * p) * mynRoot(-3 / p, 2));
        T1 = 2 * r * myCos(theta / 3);
        T2 = 2 * r * myCos((theta + 2 * PI) / 3);
        T3 = 2 * r * myCos((theta + 4 * PI) / 3);
    }

    T1 -= b / (3 * a);
    T2 = T2 - Complex(b / (3 * a), 0);
    T3 = T3 - Complex(b / (3 * a), 0);

    std::cout << PINK << "\tresult:" << GOLD << "\n\t\tX1 = " << T1 << "\n\t\tX2 = " << T2 << "\n\t\tX3 = " << T3 << std::endl;
}
