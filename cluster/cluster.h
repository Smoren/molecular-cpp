#ifndef MOLECULAR_CLUSTER_H
#define MOLECULAR_CLUSTER_H

#include <set>
#include "../atomic/atomic.h"

namespace cluster {
    class Cluster {
        explicit Cluster(math::NumericVector &position);
        [[nodiscard]] size_t length() const;
        void add(atomic::Atom &atom);
        void remove(atomic::Atom &atom);
        bool empty();

        // TODO create iterator<Atom>
    private:
        math::NumericVector position;
        std::set<atomic::Atom*> atoms = {};
    };

    class ClusterMap {
    public:
        explicit ClusterMap(int quantum);
        explicit ClusterMap(int quantum, int phase);
    private:
        std::map<math::NumericVector, Cluster*> storage = {};
        int quantum;
        int phase = 0;
    };
}

#endif //MOLECULAR_CLUSTER_H
