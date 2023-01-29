#include <iostream>
#include <vector>
#include <cmath>
#include "polyline.h"

double polyline::perimeter() const {
    check_valid();

    double l = 0;
    for (size_t pos = 0; pos < get_pnt_cnt() - 1; pos++) {
        l += geom_math::distance_pp(get_pnt_at(pos), get_pnt_at(pos+1));
    }
    return l;
}