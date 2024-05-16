#include "./atomic.h"

namespace atomic {
    size_t BondMap::length() const {
        return count;
    }

    size_t BondMap::lengthOf(size_t type) const {
        return typesCount.count(type) ? typesCount.at(type) : 0;
    }

    bool BondMap::has(Atom &atom) const {
        return storage.count(&atom) > 0;
    }

    void BondMap::add(Atom &atom) {
        storage.insert(&atom);
        if (typesCount.count(atom.getType()) == 0) {
            typesCount[atom.getType()] = 0;
        }
        typesCount[atom.getType()]++;
        count++;
    }

    void BondMap::remove(Atom &atom) {
        storage.erase(&atom);
        typesCount[atom.getType()]--;
        count--;
    }

    size_t Atom::getId() const {
        return id;
    }

    size_t Atom::getType() const {
        return type;
    }
}
