#include "cluster.h"

namespace cluster {
    bool incPoint(math::NumericVector<int> &aPoint, math::NumericVector<int> &aCenterPoint, int aDim) { // NOLINT(*-no-recursion)
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

    std::vector<math::NumericVector<int>> getNeighboursCoords(math::NumericVector<int> &coords) {
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

    math::NumericVector<int>& Cluster::getCoords() {
        return coords;
    }

    void Cluster::add(atomic::Atom &atom) {
        atoms.insert(&atom);
    }

    void Cluster::remove(atomic::Atom &atom) {
        atoms.erase(&atom);
    }

    bool Cluster::empty() {
        return atoms.empty();
    }

    std::set<atomic::Atom*>::iterator Cluster::begin() {
        return atoms.begin();
    }

    std::set<atomic::Atom*>::iterator Cluster::end() {
        return atoms.end();
    }

    ClusterMap::ClusterMap(int quantum) : quantum(quantum) {}

    ClusterMap::ClusterMap(int quantum, int phase) : quantum(quantum), phase(phase) {}

    std::vector<Cluster*> ClusterMap::getNeighbourhood(atomic::Atom &atom) {
        std::vector<Cluster*> result;
        Cluster &currentCluster = handleAtom(atom);
        for (auto &coords : getNeighboursCoords(currentCluster.getCoords())) {
            auto &cluster = getCluster(coords);
            result.push_back(&cluster);
        }
        return result;
    }

    size_t ClusterMap::countAtoms() const {
        size_t result = 0;
        for (auto &[_, cluster] : storage) {
            result += cluster.length();
        }
        return result;
    }

    Cluster& ClusterMap::getCluster(math::NumericVector<int> &clusterCoords) {
        if (storage.count(clusterCoords) == 0) {
            storage.insert({clusterCoords, Cluster(clusterCoords)});
        }
        return storage.at(clusterCoords);
    }

    Cluster& ClusterMap::handleAtom(atomic::Atom &atom) {
        Cluster &cluster = getClusterByAtom(atom);
        cluster.add(atom);
        return cluster;
        // TODO implement fully
    }

    void ClusterMap::clear() {
        storage.clear();
    }

    std::map<math::NumericVector<int>, Cluster>::iterator ClusterMap::begin() {
        return storage.begin();
    }

    std::map<math::NumericVector<int>, Cluster>::iterator ClusterMap::end() {
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
        auto clusterCoords = getClusterCoords(atom.getPosition());
        return getCluster(clusterCoords);
    }
}
