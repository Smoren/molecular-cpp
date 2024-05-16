#include <cmath>
#include "./math.h"

namespace math {
    double round(double x, int precision) {
        return std::round(x * std::pow(10, precision)) / std::pow(10, precision);
    }

    bool isEqual(double x, double y) {
        return round(x, 8) == round(y, 8);
    }
}
