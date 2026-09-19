#include <algorithm>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
class Distance;
class Weight;

namespace base {
    int calculate_delivery_price(int weight, int distance) {
        const int minDistance = 10;
        return std::max(distance, minDistance) * weight;
    }

    void example() {
        const int distance = 2;
        const int weight = 10;
        std::cout << calculate_delivery_price(distance, weight);
    }

} // namespace base

namespace motivation {

    class Distance {
    public:
        Distance(int value) : m_value{value} {
            std::cout << "Distance(" << value << ")" << std::endl;
        }
        int value() const { return m_value; }

    private:
        const int m_value;
    };

    class Weight {
    public:
        Weight(int value) : m_value{value} {
            std::cout << "Weight(" << value << ")" << std::endl;
        }

        int value() const { return m_value; }

    private:
        const int m_value;
    };

    int calculate_delivery_price(const Distance &distance, const Weight &weight) {
        const int minDistance = 10;
        return std::max(distance.value(), minDistance) * weight.value();
    }

    void example() {
        const int distance = 10;
        const int weight = 2;

        // We make a mistake - passed arguments in the wrong order.
        // Because implicit constructor, the compiler has the right to generate
        // suitable object generation.
        std::cout << calculate_delivery_price(weight, distance) << std::endl;
        // Wrong price will be computed: 100
    }

} // namespace motivation

////////////////////////////////////////////////////////////////////////////////

namespace solution {

    class Distance {
    public:
        explicit Distance(int value, int category = 0, int result = 0) : m_value{value} {
            std::cout << "Distance(" << value << ")" << std::endl;
        }

        int value() const { return m_value; }

    private:
        const int m_value;
    };

    class Weight {
    public:
        explicit Weight(int value) : m_value{value} {
            std::cout << "Weight(" << value << ")" << std::endl;
        }
        int value() const { return m_value; }

    private:
        const int m_value;
    };

    int calculate_delivery_price(const Distance &distance, const Weight &weight) {
        const int minDistance = 10;
        return std::max(distance.value(), minDistance) * weight.value();
    }

    void example() {
        const int distance = 10;
        const int weight = 2;

        // Now We can't make such a silly a mistake!
        // We should pass Distance and Weight object explicit
        std::cout << calculate_delivery_price(Distance{distance}, Weight{weight}) << std::endl;

        // Will not compile: 
//      std::cout << calculate_delivery_price(weight, distance) << std::endl;
//      std::cout << calculate_delivery_price(Weight{weight}, Distance{distance}) << std::endl;
    }

} // namespace solution

////////////////////////////////////////////////////////////////////////////////

int main() {
    motivation::example();
    solution::example();
    return 0;
}

/*

Removes conditions for mistakes "function arguments where mixed because IMPLICIT
constructs of several types have the same arguments".

Recommended to use keyword "explicit" each time when:
 - C-tor has only one argument;
 - C-tor has only one REQUIRED argument (it doesn't have a default value).

A class could have explicit and implicit constructors at the same time.
*/