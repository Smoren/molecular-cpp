#include <iostream>
#include <map>
#include "math/math.h"
#include "printer/printer.h"
#include "cluster/cluster.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    math::NumericVector<int> v1 = {1, 2, 3};
    math::NumericVector<int> v2 = {10, 20, 30};
    math::NumericVector<int> v3 = {11, 22, 33};
    std::cout << (v1 + v2) << std::endl;
    std::cout << (v1 + v2).abs() << std::endl;

    std::map<math::NumericVector<int>, int> map = {{v1, 111}, {v2, 222}, {v3, 333}};
    math::NumericVector<int> coord = {1, 2, 3};
    std::cout << map[coord] << std::endl;

    atomic::Atom atom1 = atomic::Atom(1, 1, {0, 0, 1});
    atomic::Atom atom2 = atomic::Atom(2, 2, {0, 1, 0});
    atomic::Atom atom3 = atomic::Atom(3, 2, {1, 1, 2});
    atomic::Atom atom4 = atomic::Atom(4, 1, {0, 11, 0});
    atomic::Atom atom5 = atomic::Atom(5, 2, {0, 12, 5});
    atomic::Atom atom6 = atomic::Atom(5, 2, {0, 12, 15});

    cluster::ClusterMap clusterMap = cluster::ClusterMap(10);

    clusterMap.handleAtom(atom1);
    clusterMap.handleAtom(atom2);
    clusterMap.handleAtom(atom3);
    clusterMap.handleAtom(atom4);
    clusterMap.handleAtom(atom5);
    clusterMap.handleAtom(atom6);

    for (auto& [coords, cluster] : clusterMap) {
        std::cout << "Cluster " << coords << std::endl;
        std::cout << "Size " << cluster.length() << std::endl;
        for (const auto& atom : cluster) {
            std::cout << atom->getId() << std::endl;
        }
    }

//    clusterMap.add(cluster1);
//    clusterMap.add(cluster2);
//
//    auto cluster = clusterMap.getCluster({0, 0, 0});
//    std::cout << cluster.length() << std::endl;
//
//    for (auto atom : cluster) {
//        std::cout << atom->getId() << std::endl;
//    }

    return 0;
}
