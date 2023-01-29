#include <iostream>
#include <vector>
#include <cmath>
#include "polygon.h"

#define PI 3.14159265

class regular_polygon: public polygon {
    private:
        point center_;
        point peak_;
        int n_;
    public:
        regular_polygon(point center, point peak, int n) : polygon(vec_from_data(center, peak, n)), center_(center), peak_(peak), n_(n){}
        regular_polygon(const regular_polygon &rp) : polygon(rp) {}
        regular_polygon &operator=(const regular_polygon &rp) {
            if (this != &rp) {
                peak_ = rp.peak_;
            }
            return *this;
        }
        virtual double perimeter() const;
        virtual double area() const;
    private:
        static std::vector<point> vec_from_data(const point &center, const point &peak, const int &n);
};