#ifndef MOLECULAR_CLUSTER_H
#define MOLECULAR_CLUSTER_H

#include <set>
#include "../atomic/atomic.h"
#include "../math/math.h"

namespace cluster {
    bool incPoint(math::NumericVector<int> &aPoint, math::NumericVector<int> &aCenterPoint, int aDim);
    std::vector<math::NumericVector<int>> getNeighboursCoords(math::NumericVector<int> &coords);

    class Cluster {
    public:
        explicit Cluster(math::NumericVector<int> &position);

        [[nodiscard]] size_t length() const;
        [[nodiscard]] math::NumericVector<int>& getCoords();
        void add(atomic::Atom &atom);
        void remove(atomic::Atom &atom);
        bool empty();

        // TODO create iterator<Atom>
    private:
        math::NumericVector<int> coords;
        std::set<atomic::Atom*> atoms = {};
    };

    class ClusterMap {
    public:
        explicit ClusterMap(int quantum);
        explicit ClusterMap(int quantum, int phase);

        [[nodiscard]] std::vector<Cluster*> getNeighbourhood(atomic::Atom &atom);
        [[nodiscard]] size_t countAtoms() const;
        [[nodiscard]] Cluster& getCluster(math::NumericVector<int> &clusterCoords);
        Cluster& handleAtom(atomic::Atom &atom) const;
        void clear();

    private:
        std::map<math::NumericVector<int>, Cluster> storage = {};
        int quantum;
        int phase = 0;
    };
}

#endif //MOLECULAR_CLUSTER_H
