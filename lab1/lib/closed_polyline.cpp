#include <iostream>
#include <vector>
#include <cmath>
#include "closed_polyline.h"

double closed_polyline::perimeter() const {
    check_valid();

    return polyline::perimeter() + geom_math::distance_pp(get_first_pnt(), get_last_pnt());
}
