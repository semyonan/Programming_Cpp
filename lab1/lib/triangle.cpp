#include <iostream>
#include <vector>
#include <cmath>
#include "triangle.h"

std::vector<point> triangle::vec_from_points(const point &A, const point &B, const point &C) {
    std::vector<point> result;
    result.push_back(A);
    result.push_back(B);
    result.push_back(C);
    return result;
}

double triangle::perimeter() const {
    check_valid();

    return geom_math::distance_pp(getA(), getB()) + geom_math::distance_pp(getB(), getC()) 
        + geom_math::distance_pp(getC(), getA());
}

double triangle::area() const {
    check_valid();

    return 0.5 * geom_math::distance_pl(getA(), getB(), getC()) * geom_math::distance_pp(getB(), getC());
}