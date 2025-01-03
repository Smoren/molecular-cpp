#ifndef MOLECULAR_CLUSTER_H
#define MOLECULAR_CLUSTER_H

#include <set>
#include <stack>
#include "../atomic/atomic.h"
#include "../math/math.h"

namespace cluster {
    bool incPoint(math::NumericVector<int> &aPoint, const math::NumericVector<int> &aCenterPoint, int aDim);
    std::vector<math::NumericVector<int>> getNeighboursCoords(const math::NumericVector<int> &coords);

    class Cluster {
    public:
        explicit Cluster(const math::NumericVector<int> &position);

        [[nodiscard]] size_t length() const;
        [[nodiscard]] const math::NumericVector<int>& getCoords() const;
        void add(atomic::Atom &atom);
        void remove(atomic::Atom &atom);
        [[nodiscard]] bool empty() const;
        bool operator==(const Cluster &other) const;
        bool operator<(const Cluster &other) const;
        [[nodiscard]] std::set<atomic::Atom*>::iterator begin();
        [[nodiscard]] std::set<atomic::Atom*>::iterator end();
        [[nodiscard]] std::set<atomic::Atom*>::const_iterator begin() const;
        [[nodiscard]] std::set<atomic::Atom*>::const_iterator end() const;
    private:
        math::NumericVector<int> coords;
        std::set<atomic::Atom*> atoms = {};
    };

    class ClusterMap {
    public:
        explicit ClusterMap(int quantum);
        explicit ClusterMap(int quantum, int phase);

        [[nodiscard]] std::vector<std::reference_wrapper<Cluster>> getNeighbourhood(const atomic::Atom &atom);
        [[nodiscard]] size_t length() const;
        [[nodiscard]] size_t countAtoms() const;
        [[nodiscard]] Cluster& getCluster(const math::NumericVector<int> &clusterCoords);
        [[nodiscard]] bool issetCluster(const math::NumericVector<int> &clusterCoords) const;
        Cluster& addAtom(atomic::Atom &atom);
        Cluster& handleAtom(atomic::Atom &atom, Cluster &currentCluster);
        void apply();
        void clear();
        [[nodiscard]] std::map<math::NumericVector<int>, Cluster>::iterator begin();
        [[nodiscard]] std::map<math::NumericVector<int>, Cluster>::iterator end();
        [[nodiscard]] std::map<math::NumericVector<int>, Cluster>::const_iterator begin() const;
        [[nodiscard]] std::map<math::NumericVector<int>, Cluster>::const_iterator end() const;

    private:
        [[nodiscard]] math::NumericVector<int> getClusterCoords(const math::NumericVector<double> &coords) const;
        [[nodiscard]] Cluster &getClusterByAtom(const atomic::Atom &atom);

        std::map<const math::NumericVector<int>, Cluster> storage = {};
        std::stack<std::tuple<atomic::Atom*, Cluster*, Cluster*>> moveTasks = {};
        int quantum;
        int phase = 0;
    };
}

#endif //MOLECULAR_CLUSTER_H
