#ifndef MOLECULAR_MATH_H
#define MOLECULAR_MATH_H

#include <vector>
#include <cmath>

namespace math {
    double round(double x, int precision);

    bool is_equal(double x, double y);

    class NumericVector : std::vector<double> {
    public:
        explicit NumericVector(size_t size);
        NumericVector(std::initializer_list<double> list);

        NumericVector& operator+(const NumericVector &other);
        NumericVector& operator-(const NumericVector &other);
        NumericVector& operator*(double multiplier);
        NumericVector& operator*(const NumericVector &other);
        NumericVector& operator/(double multiplier);
        NumericVector& operator/(const NumericVector &other);

        bool operator==(const NumericVector &other) const;
        bool operator!=(const NumericVector &other) const;

        NumericVector& operator=(const NumericVector &other);

        NumericVector& inverse();
        NumericVector& zero();
        NumericVector& normalize();
        NumericVector& randomize();

        [[nodiscard]] double abs() const;
        [[nodiscard]] double abs2() const;

        [[nodiscard]] bool is_normalized() const;
        [[nodiscard]] double scalar_product(const NumericVector &other) const;

        [[nodiscard]] NumericVector clone() const;
    };
}

#endif //MOLECULAR_MATH_H
