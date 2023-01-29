#include <iostream>
#include <vector>
#include <cmath>
#include "polyline.h"

#define PI 3.14159265

class closed_polyline: public polyline {
    public:
        closed_polyline(const std::vector<point> &peak) 
            : polyline(peak) {}
        closed_polyline(): polyline() {}
        closed_polyline(const closed_polyline &cp) 
            : polyline(cp) {}
        closed_polyline & operator=(const closed_polyline &cp) {
            if (this != &cp) {
                peak_ = cp.peak_;
                valid = cp.valid;
            }
            return *this;
        }

        virtual double perimeter() const;
}; 