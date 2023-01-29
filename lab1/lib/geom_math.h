#include <iostream>
#include <vector>
#include <cmath>
#include "point.h"

#define PI 3.14159265

class geom_math {
    public:
        static double distance_pp(const point &A, const point &B);
        static double distance_pl(const point &A, const point &B, const point &C);
        static bool parallel(const point &A, const point &B, const point &C, const point &D);
        static point near_point(const point &pA, const point &pB, const double &angle);
};