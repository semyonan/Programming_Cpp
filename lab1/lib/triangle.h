#include <iostream>
#include <vector>
#include <cmath>
#include "polygon.h"

#define PI 3.14159265

class triangle: public polygon {
    public:
        triangle(const point& A, const point& B, const point& C) 
            : polygon(vec_from_points(A, B, C)) {}
        triangle()
            : polygon() {}
        triangle(const triangle &t) 
            : polygon(t) {}

        triangle &operator=(const triangle &t) {
            polygon::operator=(t);
            return *this;
        }

        const point& getA() const { return peak_[0]; }
        const point& getB() const { return peak_[1]; }
        const point& getC() const { return peak_[2]; }

        virtual double area() const;
        virtual double perimeter() const;

    private:
        static std::vector<point> vec_from_points(const point &A, const point &B, const point &C);
};