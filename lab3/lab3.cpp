#include <iostream>
#include <vector>
#include "circular_buffer.h"
#include "algo.h"
#include "point.h"
#include "rational.h"

int main() {
    circular_buffer<CRational> r;
    //r.resize(10);
    r.push_front(CRational(1,2));
    r.push_front(CRational(3,4));
    r.push_front(CRational(5,6));
    r.push_front(CRational(7,8));
    r.push_back(CRational(9,10));
    r.push_back(CRational(11,12));
    r.resize(3);

    circular_buffer<point> p(10);
    p.push_front(point(1,2));
    p.push_front(point(3,4));
    p.push_front(point(5,6));
    p.push_front(point(7,8));
    p.push_front(point(9,10));
    p.push_front(point(11,12));
    p.push_front(point(5,6));
    p.push_front(point(7,8));
    p.push_front(point(9,10));
    p.push_front(point(11,12));

    /*std::vector<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    b.push_back(11);
    b.assign(3, 3);
    auto is_even = [](int const elem){ return (elem%2 == 0); };
    std::cout << (*find_backwards(b.begin(), b.end(), 0)) << std::endl;
      std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    auto is_even = [](int const elem){ return (elem < 10); };
    if (all_of(a.begin(), a.end(), is_even)) {
        std::cout << "YES" << std::endl;
    }*/
    for(auto I = r.begin(); I != r.end(); ++I) {
        std::cout << "R " << (*I) <<std::endl;
    }
    while (!r.empty()) {
        std::cout <<  "Rational "  << r.back()  << std::endl;
        r.pop_back();
    }
    while (!p.empty()) {
        std::cout <<  "Point "  << p.back()  << std::endl;
        p.pop_back();
    }

    return 0;
}

