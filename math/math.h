#ifndef MOLECULAR_MATH_H
#define MOLECULAR_MATH_H

#include <vector>
#include <cmath>
#include <iostream>

namespace math {
    double round(double x, int precision);

    bool isEqual(double x, double y);

    template <typename T> class NumericVector : public std::vector<T> {
    public:
        explicit NumericVector(size_t size);
        NumericVector(std::initializer_list<T> list);
        explicit NumericVector(const std::vector<T> &other);

        NumericVector operator +(const NumericVector &other) const;
        NumericVector operator -(const NumericVector &other) const;
        NumericVector operator *(T multiplier) const;
        NumericVector operator /(T multiplier) const;
        NumericVector operator *(const NumericVector &other) const;
        NumericVector operator /(const NumericVector &other) const;

        NumericVector& operator +=(const NumericVector &other);
        NumericVector& operator -=(const NumericVector &other);
        NumericVector& operator *=(T multiplier);
        NumericVector& operator *=(const NumericVector &other);
        NumericVector& operator /=(T multiplier);
        NumericVector& operator /=(const NumericVector &other);

        bool operator ==(const NumericVector &other) const;
        bool operator !=(const NumericVector &other) const;
        bool operator <(const NumericVector &other) const;

        NumericVector& operator =(const NumericVector &other);

        NumericVector& inverse();
        NumericVector& zero();
        NumericVector& normalize();
        NumericVector& randomize(T max = 1);

        [[nodiscard]] double abs() const;
        [[nodiscard]] double abs2() const;

        [[nodiscard]] bool isNormalized() const;
        [[nodiscard]] double scalarProduct(const NumericVector &other) const;

        [[nodiscard]] NumericVector clone() const;
    };

    template <typename T> NumericVector<T>::NumericVector(size_t size) : std::vector<T>(size) {}

    template <typename T> NumericVector<T>::NumericVector(std::initializer_list<T> list) : std::vector<T>(list) {}

    template <typename T> NumericVector<T>::NumericVector(const std::vector<T> &other) : std::vector<T>(other) {}

    template <typename T> double NumericVector<T>::abs() const {
        return std::sqrt(abs2());
    }

    template <typename T> double NumericVector<T>::abs2() const {
        auto result = 0.0;
        for (auto item: *this) {
            result += item * item;
        }
        return result;
    }

    template <typename T> NumericVector<T> NumericVector<T>::operator +(const NumericVector &other) const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i] + other[i];
        }
        return result;
    }

    template <typename T> NumericVector<T> NumericVector<T>::operator -(const NumericVector &other) const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i] - other[i];
        }
        return result;
    }

    template <typename T> NumericVector<T> NumericVector<T>::operator *(T multiplier) const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i] * multiplier;
        }
        return result;
    }

    template <typename T> NumericVector<T> NumericVector<T>::operator /(T multiplier) const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i] / multiplier;
        }
        return result;
    }

    template <typename T> NumericVector<T> NumericVector<T>::operator *(const NumericVector &other) const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i] * other[i];
        }
        return result;
    }

    template <typename T> NumericVector<T> NumericVector<T>::operator /(const NumericVector &other) const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i] / other[i];
        }
        return result;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator +=(const NumericVector &other) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] += other[i];
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator -=(const NumericVector &other) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] -= other[i];
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator *=(T multiplier) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] *= multiplier;
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator /=(T multiplier) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] /= multiplier;
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator *=(const NumericVector &other) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] *= other[i];
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator /=(const NumericVector &other) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] /= other[i];
        }
        return *this;
    }

    template <typename T> bool NumericVector<T>::operator ==(const NumericVector &other) const {
        for (int i = 0; i < this->size(); ++i) {
            if (!isEqual(static_cast<double>((*this)[i]), static_cast<double>(other[i]))) {
                return false;
            }
        }
        return true;
    }

    template <typename T> bool NumericVector<T>::operator !=(const NumericVector &other) const {
        return !(*this == other);
    }

    template <typename T> bool NumericVector<T>::operator <(const NumericVector &other) const {
        for (int i = 0; i < this->size(); ++i) {
            if ((*this)[i] > other[i]) {
                return false;
            } else if ((*this)[i] < other[i]) {
                return true;
            }
        }
        return false;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::operator =(const NumericVector &other) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] = other[i];
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::inverse() {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] = -(*this)[i];
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::zero() {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] = 0.0;
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::normalize() {
        auto norm = abs();
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] /= norm;
        }
        return *this;
    }

    template <typename T> NumericVector<T> &NumericVector<T>::randomize(T max) {
        for (int i = 0; i < this->size(); ++i) {
            (*this)[i] = (1 - 2.0 * (static_cast<double>(random()) / RAND_MAX)) * max;
        }
        return *this;
    }

    template <typename T> [[nodiscard]] bool NumericVector<T>::isNormalized() const {
        return isEqual(abs(), 1.0);
    }

    template <typename T> [[nodiscard]] double NumericVector<T>::scalarProduct(const NumericVector &other) const {
        auto result = 0.0;
        for (int i = 0; i < this->size(); ++i) {
            result += (*this)[i] * other[i];
        }
        return result;
    }

    template <typename T> [[nodiscard]] NumericVector<T> NumericVector<T>::clone() const {
        NumericVector result(this->size());
        for (int i = 0; i < this->size(); ++i) {
            result[i] = (*this)[i];
        }
        return result;
    }
}

#endif //MOLECULAR_MATH_H
