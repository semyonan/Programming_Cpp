#include <iostream>
#include <string>
#include <vector>
#include "polynomial_parser.h"

const vector<polynomial_term>& polynomial_parser::parse_polynomial() {
    
    resetCurPos();

    while (!isEOS()) {
        terms.push_back(accept_term());

        incCurPos();
    }

    return terms;
}

polynomial_term polynomial_parser::accept_term() {
    polynomial_term term;

    term.coef = accept_coefficient();
    term.exp = accept_exponent();

    return term;
}

int polynomial_parser::accept_coefficient() {
	int	coef;
	int	sign;

	accept_space();
	sign = accept_sign();
    accept_space();
	coef = accept_number();

	return coef * sign;
}

int polynomial_parser::accept_exponent() {
    int	num = 0;
    
	char* end;

    if (getCurChar() == 'x')  {
        incCurPos();

        if (getCurChar() == '^') {
            incCurPos();

            const char* start = getStrPtrFromCurPos();

            num	= strtol(start, &end, 10);

            moveCurPos(end - start);
        } else {
            num = 1;
        }
    }

	return num;
}

int polynomial_parser::accept_sign() {
	int	sign;

	sign = 1;

	if (getCurChar() == '-') {
		sign = -1;
		incCurPos();
	} else if (getCurChar() == '+') {
		incCurPos();
	}

	return sign;
}

int polynomial_parser::accept_number() {

	int	num; 
    
	char* end;

    const char* start = getStrPtrFromCurPos();

    num	= strtol(start, &end, 10);
	if (start == end) {
		num	= 1;
    }
    moveCurPos(end - start);

	return num;
}

void polynomial_parser::accept_space() {
    while (isspace(getCurChar())) {
        if (!incCurPos()) {
            break;
        }
    }
}
