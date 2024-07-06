#include <iostream>
#include <map>
#include "math/math.h"
#include "printer/printer.h"
#include "cluster/cluster.h"

void printClusterMap(const cluster::ClusterMap& clusterMap) {
    for (auto& [coords, cluster] : clusterMap) {
        std::cout << "Cluster " << coords << " (" << cluster.length() << ")" << std::endl;
        for (const auto& atom : cluster) {
            std::cout << "\t" << atom->getPosition() << std::endl;
        }
    }
}

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
    atomic::Atom atom3 = atomic::Atom(3, 2, {1, 0, 0});
    atomic::Atom atom4 = atomic::Atom(4, 1, {0, 11, 0});
    atomic::Atom atom5 = atomic::Atom(5, 2, {0, 12, 5});
    atomic::Atom atom6 = atomic::Atom(5, 2, {0, 12, 15});

    cluster::ClusterMap clusterMap = cluster::ClusterMap(10);

    clusterMap.addAtom(atom1);
    clusterMap.addAtom(atom2);
    clusterMap.addAtom(atom3);
    clusterMap.addAtom(atom4);
    clusterMap.addAtom(atom5);
    auto& cl = clusterMap.addAtom(atom6);
    atom6.setPosition({0, 0, 0});
    clusterMap.handleAtom(atom6, cl);

    printClusterMap(clusterMap);
    std::cout << "-------------------" << std::endl;

    clusterMap.apply();
    printClusterMap(clusterMap);

    return 0;
}
