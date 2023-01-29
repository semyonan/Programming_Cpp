#include <iostream>
#include <vector>
#include <cmath>

class point {
    private:
        double x_;
        double y_;
    public:
        point(double x, double y) 
            : x_(x),
              y_(y) {}
        point() 
            : x_(0),
              y_(0) {}
        point(const point &p) 
            : x_(p.x_),
              y_(p.y_) {}
        point & operator=(const point &p) {
            if (this != &p) {
                x_ = p.x_;
                y_ = p.y_;
            }
            return *this;
        }
        bool operator!=(const point &p) const {
            if ((x_ != p.x_) || (y_ != p.y_)) {
                return true;
            } else {
                return false;
            }
        }
        double getX() const {
            return this->x_;
        }
        double getY() const {
            return this->y_;
        }
};