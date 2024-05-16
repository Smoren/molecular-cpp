#include "cluster.h"

namespace cluster {
    Cluster::Cluster(math::NumericVector<int> &position) : position(position) {}

    size_t Cluster::length() const {
        return atoms.size();
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
}
