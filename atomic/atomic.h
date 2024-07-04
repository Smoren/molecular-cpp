#ifndef MOLECULAR_ATOMIC_H
#define MOLECULAR_ATOMIC_H

#include <cstdio>
#include <map>
#include <set>
#include <string>
#include "../math/math.h"

namespace atomic {
    class Atom;

    struct AtomState {
        size_t id;
        size_t type;
        std::vector<double> position;
        std::vector<double> speed;
    };

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
        Atom(size_t id, size_t type, const math::NumericVector<double>& position);
        Atom(size_t id, size_t type, const math::NumericVector<double>& position, const math::NumericVector<double>& speed);
        [[nodiscard]] size_t getId() const;
        [[nodiscard]] size_t getType() const;
        [[nodiscard]] AtomState exportState() const;
        [[nodiscard]] const math::NumericVector<double>& getPosition() const;
        [[nodiscard]] const math::NumericVector<double>& getSpeed() const;
    private:
        size_t id;
        size_t type;
        math::NumericVector<double> position;
        math::NumericVector<double> speed;
        atomic::BondMap bonds = {};
        std::vector<double> linkDistanceFactors = {};
        // TODO cluster
    };

    class Link {
    public:
        Link(Atom& lhs, Atom& rhs);
        [[nodiscard]] std::string getId() const;
        [[nodiscard]] Atom& getLhs() const;
        [[nodiscard]] Atom& getRhs() const;
        [[nodiscard]] std::vector<size_t> exportState() const;
    private:
        Atom& lhs;
        Atom& rhs;
    };
}

#endif //MOLECULAR_ATOMIC_H
