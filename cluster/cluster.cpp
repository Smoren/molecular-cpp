#include "cluster.h"

#include <functional>

namespace cluster {
    bool incPoint(math::NumericVector<int> &aPoint, const math::NumericVector<int> &aCenterPoint, int aDim) { // NOLINT(*-no-recursion)
        aPoint[aDim]++;
        if (aPoint[aDim] > aCenterPoint[aDim] + 1) {
            if (aDim == aPoint.size() - 1) {
                return false;
            }
            aPoint[aDim] = aCenterPoint[aDim] - 1;
            return incPoint(aPoint, aCenterPoint, aDim + 1);
        }
        return true;
    }

    std::vector<math::NumericVector<int>> getNeighboursCoords(const math::NumericVector<int> &coords) {
        math::NumericVector<int> curPoint = math::NumericVector<int>(coords.size());
        for (size_t i=0; i<curPoint.size(); ++i) {
            curPoint[i] = coords[i] - 1;
        }

        std::vector<math::NumericVector<int>> result;
        do {
            result.push_back(curPoint.clone());
        } while (incPoint(curPoint, coords, 0));

        return result;
    }

    Cluster::Cluster(const math::NumericVector<int> &position) : coords(position) {}

    size_t Cluster::length() const {
        return atoms.size();
    }

    const math::NumericVector<int>& Cluster::getCoords() const {
        return coords;
    }

    void Cluster::add(atomic::Atom &atom) {
        atoms.insert(&atom);
    }

    void Cluster::remove(atomic::Atom &atom) {
        atoms.erase(&atom);
    }

    bool Cluster::empty() const {
        return atoms.empty();
    }

    bool Cluster::operator==(const Cluster &other) const {
        return coords == other.coords;
    }

    bool Cluster::operator<(const Cluster &other) const {
        return coords < other.coords;
    }

    std::set<atomic::Atom*>::iterator Cluster::begin() {
        return atoms.begin();
    }

    std::set<atomic::Atom*>::iterator Cluster::end() {
        return atoms.end();
    }

    std::set<atomic::Atom*>::const_iterator Cluster::begin() const {
        return atoms.begin();
    }

    std::set<atomic::Atom*>::const_iterator Cluster::end() const {
        return atoms.end();
    }

    ClusterMap::ClusterMap(int quantum) : quantum(quantum) {}

    ClusterMap::ClusterMap(int quantum, int phase) : quantum(quantum), phase(phase) {}

    std::vector<std::reference_wrapper<Cluster>> ClusterMap::getNeighbourhood(const atomic::Atom &atom) {
        std::vector<std::reference_wrapper<Cluster>> result;
        const Cluster& currentCluster = getClusterByAtom(atom);
        for (math::NumericVector<int>& coords : getNeighboursCoords(currentCluster.getCoords())) {
            if (issetCluster(coords)) {
                result.emplace_back(getCluster(coords));
            }
        }
        return result;
    }

    size_t ClusterMap::length() const {
        return storage.size();
    }

    size_t ClusterMap::countAtoms() const {
        size_t result = 0;
        for (auto &[_, cluster] : storage) {
            result += cluster.length();
        }
        return result;
    }

    Cluster& ClusterMap::getCluster(const math::NumericVector<int> &clusterCoords) {
        if (!issetCluster(clusterCoords)) {
            storage.insert({clusterCoords, Cluster(clusterCoords)});
        }
        return storage.at(clusterCoords);
    }

    bool ClusterMap::issetCluster(const math::NumericVector<int> &clusterCoords) const {
        return storage.count(clusterCoords) > 0;
    }

    Cluster& ClusterMap::addAtom(atomic::Atom &atom) {
        Cluster &cluster = getClusterByAtom(atom);
        cluster.add(atom);
        return cluster;
    }

    Cluster& ClusterMap::handleAtom(atomic::Atom &atom, Cluster &currentCluster) {
        Cluster &actualCluster = getClusterByAtom(atom);

        if (actualCluster == currentCluster) {
            return actualCluster;
        }

        moveTasks.emplace(&atom, &currentCluster, &actualCluster);

        return actualCluster;
    }

    void ClusterMap::clear() {
        storage.clear();
    }

    void ClusterMap::apply() {
        while (!moveTasks.empty()) {
            auto [atom, clusterFrom, clusterTo] = moveTasks.top();
            moveTasks.pop();
            clusterFrom->remove(*atom);

            if (clusterFrom->empty()) {
                storage.erase(clusterFrom->getCoords());
            }

            clusterTo->add(*atom);
        }
    }

    std::map<math::NumericVector<int>, Cluster>::iterator ClusterMap::begin() {
        return storage.begin();
    }

    std::map<math::NumericVector<int>, Cluster>::iterator ClusterMap::end() {
        return storage.end();
    }

    std::map<math::NumericVector<int>, Cluster>::const_iterator ClusterMap::begin() const {
        return storage.begin();
    }

    std::map<math::NumericVector<int>, Cluster>::const_iterator ClusterMap::end() const {
        return storage.end();
    }

    math::NumericVector<int> ClusterMap::getClusterCoords(const math::NumericVector<double> &coords) const {
        math::NumericVector<int> result = math::NumericVector<int>(coords.size());
        for (size_t i=0; i<result.size(); ++i) {
            result[i] = static_cast<int>(coords[i]) / quantum + phase;
        }
        return result;
    }

    Cluster &ClusterMap::getClusterByAtom(const atomic::Atom &atom) {
        return getCluster(getClusterCoords(atom.getPosition()));
    }
}
