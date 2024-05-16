#ifndef MOLECULAR_ATOMIC_H
#define MOLECULAR_ATOMIC_H

#include <cstdio>
#include <map>
#include <set>
#include "../math/math.h"

namespace atomic {
    class Atom;

    class BondMap {
    public:
        [[nodiscard]] size_t length() const;
        [[nodiscard]] size_t lengthOf(size_t type) const;
        bool has(Atom &atom) const;
        void add(Atom &atom);
        void remove(Atom &atom);

    private:
        std::set<Atom*> storage = {};
        std::map<size_t, size_t> typesCount = {};
        size_t count = 0;
    };

    class Atom {
    public:
        [[nodiscard]] size_t getId() const;
        [[nodiscard]] size_t getType() const;
    private:
        size_t id;
        size_t type;
        math::NumericVector position;
        math::NumericVector speed;
    };
}

#endif //MOLECULAR_ATOMIC_H
