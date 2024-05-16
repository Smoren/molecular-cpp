#include <iostream>
#include "math/math.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    math::NumericVector v1 = {1.0, 2.0, 3.0};
    math::NumericVector v2 = {10.0, 20.0, 30.0};
    std::cout << (v1 + v2).abs() << std::endl;
    return 0;
}
