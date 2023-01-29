#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

static std::vector<std::string> valute_names{"AUD", "AZN", "GBP", "AMD", "BYN", "BGN", "BRL", "HUF", "HKD", "DKK", "USD", "EUR", "INR", "KZT",  "CAD", "KGS", "CNY", "MDL", "NOK", "PLN", "RON", "XDR", "SGD", "TJS", "TRY", "TMT", "UZS", "UAH", "CZK", "SEK", "CHF", "ZAR", "KRW", "JPY"};

class not_valid_valute : public std::logic_error {
    public:
        not_valid_valute(const std::string& msg)
            : std::logic_error(msg) {}
};

class Valute {
    private:
        std::string name;
        std::vector<double> values;
        double sum;
    public: 
        Valute(const std::string& NAME): name(NAME) { 
            is_valute();
        };
        void add_value(const double &value) {
            values.push_back(value);
            sum += value;
            std::cout << value << std::endl;
        }
        double get_mid() {
            sort(values.begin(), values.end());
            return values[values.size()/2];
        }
        double get_avarage() const {
            return sum/values.size();
        }
        void is_valute () const{
            for (int i = 0; i < valute_names.size(); i++) {
                if (this->name == valute_names[i]) {
                    return;
                }
            } 
            throw not_valid_valute("Not valid valute, try another valute name");
        }
};