#include <vector>
#include <cmath>
#include <initializer_list>
#include "./math.h"

namespace math {
    NumericVector::NumericVector(size_t size) : std::vector<double>(size) {}

    NumericVector::NumericVector(std::initializer_list<double> list) : std::vector<double>(list) {}

    [[nodiscard]] double NumericVector::abs() const {
        return std::sqrt(abs2());
    }

    [[nodiscard]] double NumericVector::abs2() const {
        auto result = 0.0;
        for (auto item: *this) {
            result += item * item;
        }
        return result;
    }

    NumericVector &NumericVector::operator+(const NumericVector &other) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] += other[i];
        }
        return *this;
    }

    NumericVector &NumericVector::operator-(const NumericVector &other) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] -= other[i];
        }
        return *this;
    }

    NumericVector &NumericVector::operator*(double multiplier) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] *= multiplier;
        }
        return *this;
    }

    NumericVector &NumericVector::operator/(double multiplier) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] /= multiplier;
        }
        return *this;
    }

    NumericVector &NumericVector::operator*(const NumericVector &other) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] *= other[i];
        }
        return *this;
    }

    NumericVector &NumericVector::operator/(const NumericVector &other) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] /= other[i];
        }
        return *this;
    }

    bool NumericVector::operator==(const NumericVector &other) const {
        for (int i = 0; i < size(); ++i) {
            if (!isEqual((*this)[i], other[i])) {
                return false;
            }
        }
        return true;
    }

    bool NumericVector::operator!=(const NumericVector &other) const {
        return !(*this == other);
    }

    NumericVector &NumericVector::operator=(const NumericVector &other) {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] = other[i];
        }
        return *this;
    }

    NumericVector &NumericVector::inverse() {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] = -(*this)[i];
        }
        return *this;
    }

    NumericVector &NumericVector::zero() {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] = 0.0;
        }
        return *this;
    }

    NumericVector &NumericVector::normalize() {
        auto norm = abs();
        for (int i = 0; i < size(); ++i) {
            (*this)[i] /= norm;
        }
        return *this;
    }

    NumericVector &NumericVector::randomize() {
        for (int i = 0; i < size(); ++i) {
            (*this)[i] = 1 - 2.0 * (static_cast<double>(random()) / RAND_MAX);
        }
        return *this;
    }

    [[nodiscard]] bool NumericVector::isNormalized() const {
        return isEqual(abs(), 1.0);
    }

    [[nodiscard]] double NumericVector::scalarProduct(const NumericVector &other) const {
        auto result = 0.0;
        for (int i = 0; i < size(); ++i) {
            result += (*this)[i] * other[i];
        }
        return result;
    }

    [[nodiscard]] NumericVector NumericVector::clone() const {
        NumericVector result(size());
        for (int i = 0; i < size(); ++i) {
            result[i] = (*this)[i];
        }
        return result;
    }
}
