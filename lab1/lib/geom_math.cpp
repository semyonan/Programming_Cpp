#include <iostream>
#include <vector>
#include <cmath>
#include "geom_math.h"

double geom_math::distance_pp(const point &A, const point &B) {
    return sqrt((B.getX() - A.getX())*(B.getX() - A.getX()) + (B.getY() - A.getY())*(B.getY() - A.getY()));
}

double geom_math::distance_pl(const point &A, const point &B, const point &C) {
    double dA = B.getY() - C.getY();
    double dB = B.getX() - C.getX();
    double dC = B.getX()*C.getY() - C.getX()*B.getY();
    return abs(dA*A.getX() + dB*A.getY() + dC)/sqrt(dA*dA + dB*dB);
}

bool geom_math::parallel(const point &pA, const point &pB, const point &pC, const point &pD) {
    if ((pA != pB) && (pA != pC) && (pA != pD) && (pB != pC) && (pB != pD) && (pC != pD)) {
        double A = pA.getY() - pB.getY();
        double B = pA.getX() - pB.getX();

        double A1 = pC.getY() - pD.getY();
        double B1 = pC.getX() - pD.getX();

        if (((A == 0) && (A1 == 0)) || ((B1 == 0) && (B == 0)) || ((B1 != 0) && (B != 0) && (A1 != 0) && (A != 0) && (A/A1 == B/B1))) {
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

point geom_math::near_point(const point &pA, const point &pB, const double &alpha) {
    double A = pA.getX() - pB.getX();
    double B = pA.getY() - pB.getY();
    double sn = sin(alpha);
    double cs = cos(alpha);

    double A1 = A * cs - B * sn;
    double B1 = A * sn + B * cs;
    
    return point(pA.getX() - A1, pA.getY() - B1);
}