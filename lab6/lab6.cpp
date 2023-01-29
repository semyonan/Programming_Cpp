#include "polynomial.h"
#include <gtest/gtest.h>

TEST(integer_inputs_suite, three_elements) {
    constexpr polynomial<3> p({1, 2, 3});
    static_assert(poly_in_x(p, 2) == 11, "Function isn't correct");
    EXPECT_EQ(poly_in_x(p, 2), 10) << "The polynomial degree of 2 is not correct ";
}

TEST(integer_inputs_suite, one_elements) {
    constexpr polynomial<4> p({3});
    static_assert(poly_in_x(p, 2) == 24, "Function isn't correct");
    EXPECT_EQ(poly_in_x(p, 2), 24)  << "The polynomial degree of 1 is not correct";
}

TEST(defolt_inputs_suite, zer0_element) {
    constexpr polynomial<1> p;
    static_assert(poly_in_x(p, 2) == 0, "Function isn't correct");
    EXPECT_EQ(poly_in_x(p, 2), 0) << "The polynomial degree of 0 is not correct";
} 

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}