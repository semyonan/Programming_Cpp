#include <iostream>
#include <vector>
#include <cmath>
#include "trapeze.h"

double trapeze::perimeter() const {
    check_valid();

    return geom_math::distance_pp(getA(), getB()) + geom_math::distance_pp(getB(), getC()) 
        + geom_math::distance_pp(getC(), getD()) + geom_math::distance_pp(getD(), getA());
}

double trapeze::area() const {
    check_valid();

    return 0.5 * (geom_math::distance_pp(getA(), getB()) + geom_math::distance_pp(getC(), getD())) 
        * geom_math::distance_pl(getA(), getC(), getD());
}

std::vector<point> trapeze::vec_from_points(const point &A, const point &B, const point &C, const point &D) {
    std::vector<point> result;
    result.push_back(A);
    result.push_back(B);
    result.push_back(C);
    result.push_back(D);
    return result;
}