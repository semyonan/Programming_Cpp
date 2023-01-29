#include <iostream>
#include <vector>
#include <cmath>
#include "objects.h"

#define PI 3.14159265

class polyline : public object_with_points {
    public:
        polyline() { valid = NOT_VALID; }
        polyline(const std::vector<point> &peak)
            : object_with_points(peak) {
                valid = PRE_VALID;
                if (!is_valid()) {
                    throw std::invalid_argument("Wrong polyline points");
                } else {
                    valid = VALID;
                }
            }
        
        polyline(const polyline &p) 
            : object_with_points(p.peak_) { valid = p.valid; }
        polyline & operator=(const polyline &p) {
            if (this != &p) {
                peak_ = p.peak_;
                valid = p.valid;
            }
            return *this;
        }
        virtual double perimeter() const;
};