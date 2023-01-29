#include <iostream>
#include <vector>
#include <cmath>
#include "lib/polynomial.h"
#include "lib/polyline.h"

int main() {
    /*std::vector<int> poly;
        poly.push_back(0);
        poly.push_back(2);
        poly.push_back(0);
        poly.push_back(0);
        poly.push_back(0);
        poly.push_back(-1);
        polynomial p(poly);
        polynomial p1(poly);
        polynomial pp = p1 * p;*/
    polynomial p;
    std::cin >> p;
    std::cout << p << std::endl;
    std::vector<point> poly;
        poly.push_back(point(0,0));
        poly.push_back(point(1,0));
        poly.push_back(point(0,2));
        polyline tr(poly);
    std::cout << "Test: " << tr.perimeter() << std::endl;
    //regular_polygon rp(point(0,0), point(1,2), 4);
    //std::cout << "Test: " << rp.area() << std::endl;

    /*try {
        std::vector<point> poly;
        poly.push_back(point(0,0));
        poly.push_back(point(1,0));
        poly.push_back(point(0,2));
        trapeze tr1(point(0,0), point(4,0), point(1,1), point(0,1));
        trapeze tr3;
        trapeze tr2 = tr3;
        
        std::cout << "Test: " << tr2.perimeter() << std::endl;
    } catch (std::invalid_argument ex) {
        std::cout << ex.what() << std::endl;
    } catch (not_valid_object ex) {
        std::cout << ex.what() << std::endl;
    }*/

    return 0;
};