#include <iostream>
#include <vector>
#include <cmath>

class polynomial {
    private:
        std::vector<int> coef_;
    public:
        polynomial(std::vector<int> coef): 
            coef_(coef) {}
        polynomial() { coef_.push_back(0); }    
        polynomial &operator=(const polynomial &A) {
            if (this != &A) {
                coef_ = A.coef_;
            }
            return *this;
        }
        bool operator==(const polynomial &A) const;
        bool operator!=(const polynomial &A) const;
        polynomial operator+(const polynomial &A) const;
        polynomial &operator++();
        polynomial operator-(const polynomial &A) const;
        polynomial &operator--();
        polynomial &operator+=(const polynomial &A);
        polynomial &operator-=(const polynomial &A);
        polynomial operator*(const int &a) const;
        polynomial operator*(const polynomial &A) const;
        polynomial operator/(const int &a) const;
        polynomial &operator*=(const int &a);
        polynomial &operator*=(const polynomial &A);
        polynomial &operator/=(const int &a);
        double operator[](const int &i) const;
        std::vector<int> get_coef() const;
        char get_sign(const int &i) const;
        friend std::istream& operator>>(std::istream& in, polynomial &p);
};

std::ostream& operator<<(std::ostream& out, const polynomial &p);