#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace lab_bigint {

class bigint {
private:
    std::vector<int> digits;
    int max_quantity_of_digits = static_cast<int>(log10(BASE));

public:
    explicit bigint(const std::string &input_string = "0") {
        size_t size_of_string = input_string.size();
        std::string currrent_number = "";
        int current_class_of_number = 0;
        for (int digit = static_cast<int>(size_of_string) - 1; digit >= 0;
             digit--) {
            currrent_number = input_string[digit] + currrent_number;
            current_class_of_number += 1;
            if (digit == 0 &&
                current_class_of_number < max_quantity_of_digits) {
                digits.push_back(std::stoi(currrent_number));
                break;
            }
            if (current_class_of_number == max_quantity_of_digits) {
                digits.push_back(std::stoi(currrent_number));
                current_class_of_number = 0;
                currrent_number = "";
            }
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    // cppcheck-suppress noExplicitConstructor
    bigint(unsigned int input_int) : bigint(std::to_string(input_int)){};

    friend std::ostream &
    operator<<(std::ostream &os, const bigint &right_hand_side) {
        std::string output = right_hand_side.to_string();
        os << output;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, bigint &right_hand_side) {
        std::string input;
        is >> input;
        right_hand_side.digits = bigint(input).digits;
        return is;
    }

    friend bool
    operator==(const bigint &left_hand_side, const bigint &right_hand_side) {
        return left_hand_side.digits == right_hand_side.digits;
    }

    friend bool
    operator!=(const bigint &left_hand_side, const bigint &right_hand_side) {
        return left_hand_side.digits != right_hand_side.digits;
    }

    friend bool
    operator>(const bigint &left_hand_side, const bigint &right_hand_side) {
        if (left_hand_side.digits.size() != right_hand_side.digits.size()) {
            return left_hand_side.digits.size() > right_hand_side.digits.size();
        }
        for (int digit = left_hand_side.digits.size(); digit >= 1; digit--) {
            if (left_hand_side.digits[digit - 1] !=
                right_hand_side.digits[digit - 1]) {
                return left_hand_side.digits[digit - 1] >
                       right_hand_side.digits[digit - 1];
            }
        }
        return false;
    }

    friend bool
    operator<(const bigint &left_hand_side, const bigint &right_hand_side) {
        return right_hand_side > left_hand_side;
    }

    friend bool
    operator>=(const bigint &left_hand_side, const bigint &right_hand_side) {
        return (
            (left_hand_side > right_hand_side) ||
            (left_hand_side == right_hand_side)
        );
    }

    friend bool
    operator<=(const bigint &left_hand_side, const bigint &right_hand_side) {
        return (
            (left_hand_side < right_hand_side) ||
            (left_hand_side == right_hand_side)
        );
    }

    std::string to_string() const {
        std::string digits_to_string;
        for (int digit : digits) {
            for (int quantity = 0; quantity < max_quantity_of_digits;
                 quantity++) {
                digits_to_string += static_cast<char>(digit % 10 + '0');
                digit /= 10;
            }
        }
        while (digits_to_string.size() > 1 && digits_to_string.back() == '0') {
            digits_to_string.pop_back();
        }
        std::reverse(digits_to_string.begin(), digits_to_string.end());
        return digits_to_string;
    }

    explicit operator unsigned int() {
        unsigned int digits_in_unsigned_int = std::stoi(this->to_string());
        return static_cast<unsigned int>(digits_in_unsigned_int);
    }

    bigint &operator+=(bigint right_hand_side) {
        size_t max_length =
            std::max(digits.size(), right_hand_side.digits.size() + 1);
        for (size_t digit = 0; digit < max_length; ++digit) {
            bool check = false;
            if (digit + 1 >= digits.size()) {
                digits.push_back(0);
            }
            if (digit < right_hand_side.digits.size()) {
                digits[digit] += right_hand_side.digits[digit];
                check = true;
            }

            if (digits[digit] >= BASE) {
                digits[digit + 1] += 1;
                digits[digit] -= BASE;
                check = true;
            }
            if (check != true) {
                break;
            }
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    bigint &operator-=(bigint right_hand_side) {
        size_t min_length =
            std::min(digits.size(), right_hand_side.digits.size());
        size_t max_length =
            std::max(digits.size(), right_hand_side.digits.size());
        for (size_t digit = 0; digit < min_length; digit++) {
            digits[digit] -= right_hand_side.digits[digit];
            if (digit > 0 && digits[digit - 1] < 0) {
                digits[digit - 1] += BASE;
                digits[digit] -= 1;
            }
        }
        for (size_t digit = min_length; digit < max_length; digit++) {
            if (digits[digit - 1] < 0) {
                digits[digit - 1] += BASE;
                digits[digit] -= 1;
            }
        }
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        return *this;
    }

    friend bigint operator+(  // cppcheck-suppress unmatchedSuppression
        bigint left_hand_side,
        const bigint &right_hand_side
    ) {
        return (left_hand_side += right_hand_side);
    }

    friend bigint operator-(  // cppcheck-suppress unmatchedSuppression
        const bigint &left_hand_side,
        const bigint &right_hand_side
    ) {
        bigint resul_sum = left_hand_side;
        return (resul_sum -= right_hand_side);
    }

    bigint operator++() {
        *this += 1;
        return *this;
    }

    bigint operator++(int) {
        bigint old_value = *this;
        *this += 1;
        return old_value;
    }

    bigint operator--() {
        *this -= 1;
        return *this;
    }

    bigint operator--(int) {
        bigint old_value = *this;
        *this -= 1;
        return old_value;
    }
};
}  // namespace lab_bigint
