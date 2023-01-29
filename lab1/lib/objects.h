#include <iostream>
#include <vector>
#include <cmath>
#include "exeptions.h"
#include "geom_math.h"

#define PI 3.14159265

class object_with_points {

    protected:
        std::vector<point> peak_;
        status valid;
    public:

        object_with_points() {}

        object_with_points(const std::vector<point> &peak)
            : peak_(peak) {}

        bool is_valid() const {
            return ((get_pnt_cnt() > 2) && (perimeter() > geom_math::distance_pp(get_first_pnt(), get_last_pnt())));
        }

        virtual double perimeter() const = 0;

    protected:

        size_t get_pnt_cnt() const {
            return peak_.size();
        }

        const point& get_first_pnt() const {
            return peak_[0];
        }

        const point& get_last_pnt() const {
            return peak_[peak_.size()-1];
        }

        size_t get_last_ind() const {
            return peak_.size()-1;
        }

        const point& get_pnt_at(size_t pos) const {
            return peak_[pos];
        }

        void check_valid() const {
            if (valid == NOT_VALID) {
                throw not_valid_object("Not valid object");
            }
        }
};