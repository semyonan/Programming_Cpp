#include <iostream>
#include <vector>
#include <cmath>
#include "polynomial.h"
#include "polynomial_parser.h"

bool polynomial::operator==(const polynomial &A) const {
    if (A.coef_.size() == this->coef_.size()) {
        for (int i = 0; i < A.coef_.size(); i++) {
            if (A.coef_[i] != this->coef_[i]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
bool polynomial::operator!=(const polynomial &A) const {
    return !(*this == A);
}
polynomial polynomial::operator+(const polynomial &A) const {
    std::vector<int> new_coef_;

    int i = 0;
    while ((i < A.coef_.size()) && (i < this->coef_.size())) {
        new_coef_.push_back(this->coef_[i] + A.coef_[i]);
        i++;
    }
    while (i < A.coef_.size()) {
        new_coef_.push_back(A.coef_[i]);
        i++;
    }
    while (i < this->coef_.size()) {
        new_coef_.push_back(this->coef_[i]);
        i++;
    }

    polynomial result(new_coef_);
    return result;
}
polynomial& polynomial::operator++() {
    for (int i = 0; i < this->coef_.size(); i++) {
        this->coef_[i]++;
    }
    return *this;
}
polynomial polynomial::operator-(const polynomial &A) const {
    return *this + (A * (-1));
}
polynomial& polynomial::operator--() {
    for (int i = 0; i < this->coef_.size(); i++) {
        this->coef_[i]--;
    }
    return *this;
}
polynomial& polynomial::operator+=(const polynomial &A) {
    *this = (*this) + A;
    return *this;
}
polynomial& polynomial::operator-=(const polynomial &A) {
    *this = (*this) - A;
    return *this;
}
polynomial polynomial::operator*(const int &a) const {
    polynomial result = *this;
    for (int i = 0; i < this->coef_.size(); i++) {
        result.coef_[i] *= a;
    }
    return result;
}
polynomial polynomial::operator*(const polynomial &A) const {
    polynomial result;
    for (int j = 0; j < A.coef_.size(); j++) {
        for (int i = 0; i < this->coef_.size(); i++) {
            while (result.coef_.size() <= i+j) {
                result.coef_.push_back(0);
            }
            result.coef_[i+j] += A.coef_[j] * (this->coef_[i]);
        }
    }
    return result;
}
polynomial polynomial::operator/(const int &a) const {
    polynomial result = *this;
    for (int i = 0; i < this->coef_.size(); i++) {
        result.coef_[i] /= a;
    }
    return result;
}
polynomial& polynomial::operator*=(const int &a) {
    *this = (*this) * a;
    return *this;
}
polynomial& polynomial::operator*=(const polynomial &A) {
    *this = (*this) * A;
    return *this;
}
polynomial& polynomial::operator/=(const int &a) {
    *this = (*this) / a;
    return *this;
}

double polynomial::operator[](const int &i) const{
    if (i < this->coef_.size()) {
        return this->coef_[i];
    }
    return 0;
}

char polynomial::get_sign(const int &i) const {
    if (coef_[i] > 0) {
        return '+';
    } else {
        return '-';
    }
}

std::vector<int> polynomial::get_coef() const {
    return coef_;
}

std::istream& operator>>(std::istream& in, polynomial &p) {
    string polynomial_string;

    // 'cin >> string' reads till space only
    getline(in, polynomial_string);

    polynomial_parser parser(polynomial_string);

    const vector<polynomial_term>& terms = parser.parse_polynomial(); 

    p.coef_.resize(terms[0].exp+1);
    int cur_exp = terms[0].exp;
    for (size_t i = 0; i < terms.size(); ++i) {
        while (cur_exp != terms[i].exp) {
            p.coef_[cur_exp] = 0;
            cur_exp--;
        }
        p.coef_[terms[i].exp] = terms[i].coef;
        cur_exp--;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const polynomial &p) {
    std::vector<int> coef = p.get_coef();
    char sign = ' ';

    for (int i = coef.size()-1; i >= 0; i--) {
        if (coef[i] != 0) {
            if ((sign == ' ') && (p.get_sign(i)) == '-') {
                sign = '-';
            } else if (sign != ' ') {
                sign = p.get_sign(i);
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
}