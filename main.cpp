#include <iostream>
#include <map>
#include "math/math.h"
#include "cluster/cluster.h"
#include "printer/base.h"
#include "printer/cluster.h"

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

    auto atom1 = atomic::Atom(1, 1, {0, 0, 1});
    auto atom2 = atomic::Atom(2, 2, {0, 1, 0});
    auto atom3 = atomic::Atom(3, 2, {1, 0, 0});
    auto atom4 = atomic::Atom(4, 1, {0, 11, 0});
    auto atom5 = atomic::Atom(5, 2, {0, 12, 5});
    auto atom6 = atomic::Atom(5, 2, {0, 12, 15});

    auto clusterMap = cluster::ClusterMap(10);

    clusterMap.addAtom(atom1);
    clusterMap.addAtom(atom2);
    clusterMap.addAtom(atom3);
    clusterMap.addAtom(atom4);
    clusterMap.addAtom(atom5);

    auto& cl = clusterMap.addAtom(atom6);
    atom6.setPosition({0, 0, 0});
    clusterMap.handleAtom(atom6, cl);

    std::cout << clusterMap << std::endl;

    clusterMap.apply();
    std::cout << clusterMap << std::endl;

    std::cout << clusterMap.getNeighbourhood(atom1);

    return 0;
}
