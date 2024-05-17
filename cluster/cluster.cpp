#include "cluster.h"

namespace cluster {
    bool incPoint(math::NumericVector<int> &aPoint, math::NumericVector<int> &aCenterPoint, int aDim) {
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

    Cluster::Cluster(math::NumericVector<int> &position) : coords(position) {}

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

    Cluster& ClusterMap::handleAtom(atomic::Atom &atom) const {
        // TODO
    }

    void ClusterMap::clear() {
        storage.clear();
    }
}
