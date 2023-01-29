#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>

template<std::size_t N>
class polynomial {
    private:
        std::array<int, N> coef_;
        char get_sign(const int &i) const { return coef_[i] > 0 ? '+' : '-' ; }
    public:
        constexpr polynomial(const std::array<int, N>& coef) : coef_(coef) {}
        constexpr polynomial() : coef_({0}) {}    
        polynomial &operator=(const polynomial &A) {
            if (this != &A) {
                coef_ = A.coef_;
            }
            return *this;
        }
        constexpr int operator[](const int &i) const { return i < this->coef_.size() ? this->coef_[i] : 0; }
        std::array<int, N> get_coef() const { return coef_; }
        constexpr std::size_t size() const { return coef_.size(); } 
        friend std::ostream& operator<<(std::ostream& out, const polynomial<N> &p);
};

template<std::size_t N>
std::ostream& operator<<(std::ostream& out, const polynomial<N> &p) {
    std::array<int, N> coef = p.get_coef();
    std::reverse(coef.begin(), coef.end());
    char sign = ' ';

    for (int i = p.size()-1 ; i >= 0; i--) {
        if (coef[i] != 0) {
            if ((sign == ' ') && (p.get_sign(p.size() - i)) == '-') {
                sign = '-';
            } else if (sign != ' ') {
                sign = p.get_sign(p.size() - i);
            }

            if (i == 0) {
                out << sign << abs(coef[i]);
            }  else if (i == 1) {
                if (abs(coef[i]) == 1) {
                    out << sign << "x";
                } else {
                    out << sign << abs(coef[i]) << "x";
                }
            } else {
                if (abs(coef[i]) == 1) {
                    out << sign << "x^" << i;
                } else {
                    out << sign << abs(coef[i]) << "x^" << i;
                }

            }
            if (sign == ' ') {
                sign = p.get_sign(i);
            }
        }
    }
    return out;
}; 

template<std::size_t N>
constexpr int poly_in_x(const polynomial<N> &p, const int &x, int result = 0, std::size_t n = 0) {
    return n == p.size() ? result : 
           n == 0 ? poly_in_x(p, x, result + p[n], n + 1) :
                           poly_in_x(p, x, result*x + p[n], n + 1);
}
