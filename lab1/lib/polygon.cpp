#include <iostream>
#include <vector>
#include <cmath>
#include "polygon.h"

double polygon::perimeter() const {
    check_valid();

    double l = 0;
    for (size_t pos = 0; pos < get_pnt_cnt() - 1; pos++) {
        l += geom_math::distance_pp(get_pnt_at(pos), get_pnt_at(pos+1));
    }
    l += geom_math::distance_pp(get_last_pnt(), get_first_pnt());
    return l;
}

double polygon::area() const {
    check_valid(); 

    double p1 = 0, p2 = 0;
    for (size_t pos = 0; pos < get_pnt_cnt() - 1; pos++) {
        p1 += get_pnt_at(pos).getX() * get_pnt_at(pos+1).getY();
        p2 += get_pnt_at(pos).getY() * get_pnt_at(pos+1).getX();
    }
    p1 += get_last_pnt().getX() * get_first_pnt().getY();
    p2 += get_last_pnt().getY() * get_first_pnt().getX();
    return (p1 - p2)/2;
}