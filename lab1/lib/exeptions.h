#include <iostream>
#include <vector>
#include <cmath>

enum status{VALID, PRE_VALID, NOT_VALID};

class not_valid_object : public std::logic_error {
    public:
        not_valid_object(const std::string& msg)
            : std::logic_error(msg) {}
};