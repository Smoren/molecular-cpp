#include <string>
#include "./atomic.h"

namespace atomic {
    size_t BondMap::length() const {
        return count;
    }

    size_t BondMap::lengthOf(const size_t type) const {
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

    Atom::Atom(const size_t id, const size_t type, const math::NumericVector<double>& position) :
        id(id),
        type(type),
        position(position),
        speed(math::NumericVector<double>(position.size())) {}

    Atom::Atom(const size_t id, const size_t type, const math::NumericVector<double>& position, const math::NumericVector<double>& speed) :
        id(id),
        type(type),
        position(position),
        speed(speed) {}

    Atom::Atom(const AtomState& state) :
        id(state.id),
        type(state.type),
        position(state.position),
        speed(state.speed) {}

    size_t Atom::getId() const {
        return id;
    }

    size_t Atom::getType() const {
        return type;
    }

    AtomState Atom::exportState() const {
        return { id, type, position, speed };
    }

    math::NumericVector<double>& Atom::getPosition() {
        return position;
    }

    const math::NumericVector<double>& Atom::getPosition() const {
        return position;
    }

    void Atom::setPosition(const math::NumericVector<double>& value) {
        position = value;
    }

    math::NumericVector<double>& Atom::getSpeed() {
        return speed;
    }

    const math::NumericVector<double>& Atom::getSpeed() const {
        return speed;
    }

    void Atom::setSpeed(const math::NumericVector<double>& value) {
        speed = value;
    }

    bool Atom::operator==(const Atom &other) const {
        return id == other.id;
    }

    bool Atom::operator<(const Atom &other) const {
        return id < other.id;
    }

    Link::Link(Atom& lhs, Atom& rhs) : lhs(lhs), rhs(rhs) {}

    std::string Link::getId() const {
        return std::to_string(lhs.getId()) + '-' + std::to_string(rhs.getId());
    }

    Atom& Link::getLhs() const {
        return lhs;
    }

    Atom& Link::getRhs() const {
        return rhs;
    }

    std::vector<size_t> Link::exportState() const {
        return {lhs.getId(), rhs.getId()};
    }

    bool Link::operator==(const Link &other) const {
        return getId() == other.getId();
    }

    bool Link::operator<(const Link &other) const {
        return getId() < other.getId();
    }
}
