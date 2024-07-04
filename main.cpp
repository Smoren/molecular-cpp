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

    atomic::Atom atom1 = atomic::Atom(1, 2, {1, 2, 3});
    atomic::Atom atom2 = atomic::Atom(2, 2, {1, 2, 3});

    cluster::Cluster cluster = cluster::Cluster({1, 2, 3});
    cluster.add(atom1);
    cluster.add(atom2);
    std::cout << cluster.length() << std::endl;

    for (auto atom : cluster) {
        std::cout << atom->getId() << std::endl;
    }

    return 0;
}
