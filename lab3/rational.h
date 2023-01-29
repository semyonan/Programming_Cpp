#include <iostream>

class CRational {
    public:
    CRational(int numerator=0 , unsigned denominator=1) // default constructor
    : numerator_(numerator)
    , denominator_(denominator)
    {}
    int numerator() const {
        return numerator_;
    }
    unsigned denominator() const {
        return denominator_;
    }
    CRational& operator=(const CRational& other) {
        if(&other == this){
        return *this;
        }

        numerator_ = other.numerator_;
        denominator_ = other.denominator_;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& stream, const CRational& value) ;
    friend std::istream& operator>>(std::istream& stream, CRational& r);
    private:
        int numerator_;
        unsigned denominator_;
};

std::ostream& operator<<(std::ostream& stream, const CRational& value) {
    stream << value.numerator() << '/' << value.denominator();
    return stream;
}

std::istream& operator>>(std::istream& stream, CRational& r) {
    int a;
    unsigned b;
    char ch;
    stream >> a;
    if (stream.get() != '/')
    stream.setstate(std::ios::failbit);
    stream >> b;

    r = CRational(a,b);
    return stream;
}
