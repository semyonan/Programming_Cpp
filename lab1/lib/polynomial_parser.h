#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct polynomial_term {
    int coef;
    int exp;
    polynomial_term(int coef, int exp)
        : coef(coef), exp(exp) {}
    polynomial_term()
        : coef(0), exp(0) {}
};

class polynomial_parser {
    private:
        string string_representation;
        size_t cur_pos; // current position in the string
        const size_t str_len; // length of the string

        vector<polynomial_term> terms;

    public:
        polynomial_parser(string &value) 
            : string_representation(value), 
            cur_pos(0), str_len(value.length()) {}

        const vector<polynomial_term>& parse_polynomial();

    private:

        polynomial_term accept_term();

        int accept_coefficient();
        int accept_exponent();
        int accept_sign();
        int accept_number();
        void accept_space();

        // is end of string
        const bool isEOS() const {
            return (cur_pos < 0) || (cur_pos >= str_len);
        }

        // get character in current position, or '\0' if current position is out of string
        char getCurChar() const {
            return isEOS() ? '\0' : string_representation[cur_pos]; 
        }

        // increment current position, returns whether current position is inside string
        bool incCurPos() {
            if (!isEOS()) {
                ++cur_pos;
            }
            return !isEOS();
        }

        // move current position to specified number of characters
        bool moveCurPos(size_t count) {
            if (!isEOS()) {
                cur_pos = min<size_t>(str_len, cur_pos+count);
            }
            return !isEOS();  
        }

        // returns pointer to substring that starts from current position
        const char* getStrPtrFromCurPos() const {
            return isEOS() ? nullptr : (string_representation.c_str() + cur_pos);
        }

        // reset current position in the string
        void resetCurPos() {
            cur_pos = 0;
        }
        
};