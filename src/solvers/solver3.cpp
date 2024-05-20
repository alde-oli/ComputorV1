#include "computor.hpp"

// aX^3 + bX^2 + cX + d = 0
//[3]    [2]    [1]  [0]


void solver3(std::map<size_t, double> &polynom) {
    double p = (3 * polynom[3] * polynom[1] - myPow(polynom[2], 2)) / (3 * myPow(polynom[3], 2));
    double q = (2 * myPow(polynom[2], 3) - 9 * polynom[3] * polynom[2] * polynom[1] + 27 * myPow(polynom[3], 2) * polynom[0]) / (27 * myPow(polynom[3], 3));

    double delta = myPow(q / 2, 2) + myPow(p / 3, 3);

	std::cout << "delta: " << delta << std::endl;

    double T1 = 0;
    Complex T2, T3;

    if (delta > 0) {
        T1 = mynRoot(-(q / 2) + mynRoot(delta, 2), 3) + mynRoot(-(q / 2) - mynRoot(delta, 2), 3);
        T2 = Complex(-T1 / 2, mynRoot(3, 2) / 2 * (T1 < 0 ? -T1 : T1));
        T3 = T2.conjugate();
    } else if (delta == 0) {
        T1 = 3 * q / p;
        T2 = T3 = -3 * q / (2 * p);
    } else {
        double theta = myArcCos((3 * q) / (2 * p) * mynRoot(-3 / p, 2));
        T1 = 2 * mynRoot(-p / 3, 2) * myCos(theta / 3);
        T2 = 2 * mynRoot(-p / 3, 2) * myCos((theta + 2 * PI) / 3);
        T3 = 2 * mynRoot(-p / 3, 2) * myCos((theta + 4 * PI) / 3);
    }

    T1 -= polynom[2] / (3 * polynom[3]);
    T2 = T2 - Complex(polynom[2] / (3 * polynom[3]), 0);
    T3 = T3 - Complex(polynom[2] / (3 * polynom[3]), 0);

    std::cout << "result:\n\tX1 = " << T1 << "\n\tX2 = " << T2 << "\n\tX3 = " << T3 << std::endl;
}
