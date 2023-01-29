#include <iostream>
#include <chrono>
#include "custom_allocator.h"

int main( ){
    std::vector <int, custom_allocator<int>> v1(3);
    custom_allocator<int> al({20, 8, 4, 16}, {1, 2, 4, 1});

    custom_allocator<double> al2(al);
    custom_allocator<int> al3, al4({4, 8, 12, 16}, {1, 2, 1, 4});
    al3 = al4;
    if (al == al2) {
        std::cout << "Al == al2 "<< std::endl;
    }
    if (al3 == al) {
        std::cout << "Al3 == al "<< std::endl;
    }
    if (al3 == al4) {
        std::cout << "Al3 == al4 "<< std::endl;
    }

    std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
    std::vector<int, custom_allocator<int> > v(8);
    v.push_back(10);
    v.push_back(15);
    v.push_back(20);
    v.push_back(14);
    v.clear();
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    std::vector<int> v2(8);
    v.push_back(10);
    v.push_back(15);
    v.push_back(20);
    v.push_back(14);
    v.clear();
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::cout << "Custom_allocator work for " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << " microseconds" << std::endl;
    std::cout << "Std::allocator work for " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << " microseconds" << std::endl;

    return 0;
};