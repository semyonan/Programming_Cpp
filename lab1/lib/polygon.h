#include <iostream>
#include <vector>
#include <cmath>
#include "objects.h"

#define PI 3.14159265

class polygon : public object_with_points {
    public:
        polygon() { valid = NOT_VALID; }
        polygon(const std::vector<point> &peak) 
            : object_with_points(peak) {
                valid = PRE_VALID;
                if (!is_valid()) {
                    throw std::invalid_argument("Wrong polygon points");
                } else {
                    valid = VALID;
                }
            }
        polygon(const polygon &p) 
            : object_with_points(p.peak_) { valid = p.valid; }
        polygon &operator=(const polygon &p) {
            if (this != &p) {
                peak_ = p.peak_;
                valid = p.valid;
            }
            return *this;
        }
        virtual double perimeter() const;
        virtual double area() const;
};