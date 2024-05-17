#ifndef MOLECULAR_CLUSTER_H
#define MOLECULAR_CLUSTER_H

#include <set>
#include "../atomic/atomic.h"
#include "../math/math.h"

namespace cluster {
    bool incPoint(math::NumericVector<int> &aPoint, math::NumericVector<int> &aCenterPoint, int aDim);
    std::vector<math::NumericVector<int>> getNeighborhoodCoords(math::NumericVector<int> &coords);

    class Cluster {
        explicit Cluster(math::NumericVector<int> &position);
        [[nodiscard]] size_t length() const;
        void add(atomic::Atom &atom);
        void remove(atomic::Atom &atom);
        bool empty();

        // TODO create iterator<Atom>
    private:
        math::NumericVector<int> position;
        std::set<atomic::Atom*> atoms = {};
    };

    class ClusterMap {
    public:
        explicit ClusterMap(int quantum);
        explicit ClusterMap(int quantum, int phase);
    private:
        std::map<math::NumericVector<int>, Cluster*> storage = {};
        int quantum;
        int phase = 0;
    };
}

#endif //MOLECULAR_CLUSTER_H
