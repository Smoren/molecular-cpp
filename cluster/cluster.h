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
        explicit Cluster(const math::NumericVector<int> &position);

        [[nodiscard]] size_t length() const;
        [[nodiscard]] math::NumericVector<int>& getCoords();
        void add(atomic::Atom &atom);
        void remove(atomic::Atom &atom);
        bool empty();
        std::set<atomic::Atom*>::iterator begin();
        std::set<atomic::Atom*>::iterator end();
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
        Cluster& handleAtom(atomic::Atom &atom);
        void clear();
        std::map<math::NumericVector<int>, Cluster>::iterator begin();
        std::map<math::NumericVector<int>, Cluster>::iterator end();

    private:
        [[nodiscard]] math::NumericVector<int> getClusterCoords(const math::NumericVector<double> &coords) const;
        [[nodiscard]] Cluster &getClusterByAtom(const atomic::Atom &atom);

        std::map<math::NumericVector<int>, Cluster> storage = {};
        int quantum;
        int phase = 0;
    };
}

#endif //MOLECULAR_CLUSTER_H
