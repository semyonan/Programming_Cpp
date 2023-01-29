#include <iostream>
#include <vector>
#include <cmath>
#include "regular_polygon.h"

double regular_polygon::perimeter() const {
    check_valid();

    return geom_math::distance_pp(get_first_pnt(), get_last_pnt()) * get_pnt_cnt();
}

double regular_polygon::area() const {
    check_valid();

    double r = (geom_math::distance_pp(center_, peak_)/(2 * sin(PI/get_pnt_cnt()))) * cos(PI/get_pnt_cnt());
    return 0.5 * this->perimeter() * r;
}

std::vector<point> regular_polygon::vec_from_data(const point &center, const point &peak, const int &n) {
    std::vector<point> result;
    double angle = (360 * PI)/(180 * n);
    point tmp = peak;


    for (int i = 0; i < n; i++) {
        result.push_back(tmp);
        tmp = geom_math::near_point(center, tmp, angle);
    }

    return result;
}