#include <iostream>
#include <vector>
#include <cmath>
#include "polygon.h"

#define PI 3.14159265

class trapeze: public polygon {
    public:
        trapeze(const point& A, const point& B, const point& C, const point& D) 
            : polygon(vec_from_points(A, B, C, D)) {
                if (!is_valid()) {
                    throw std::invalid_argument("Wrong trapeze points");
                } 
            }
        trapeze()
            : polygon() {}
        trapeze(const trapeze &t) 
            : polygon(t) {}

        const point& getA() const { return peak_[0]; }
        const point& getB() const { return peak_[1]; }
        const point& getC() const { return peak_[2]; }
        const point& getD() const { return peak_[3]; }

        bool is_valid() const {
            return (((geom_math::parallel(getA(), getB(), getC(), getD()) == 1) && (geom_math::parallel(getA(), getD(), getB(), getC()) == 0)) 
                    || ((geom_math::parallel(getA(), getB(), getC(), getD()) == 0) && (geom_math::parallel(getA(), getD(), getB(), getC()) == 1)));
        }

        virtual double perimeter() const;
        virtual double area() const;

    private:
        static std::vector<point> vec_from_points(const point &A, const point &B, const point &C, const point &D);
}; 