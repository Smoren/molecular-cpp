#ifndef MOLECULAR_PRINTER_CLUSTER_H
#define MOLECULAR_PRINTER_CLUSTER_H

#include <iostream>
#include "./base.h"
#include "../cluster/cluster.h"

std::ostream& operator <<(std::ostream& stream, const cluster::Cluster& cluster) {
    stream << "Cluster " << cluster.getCoords() << " (size: " << cluster.length() << ")" << std::endl;
    for (const auto& atom : cluster) {
        std::cout << "\t" << atom->getPosition() << std::endl;
    }
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const cluster::ClusterMap& clusterMap) {
    for (auto& [coords, cluster] : clusterMap) {
        stream << cluster;
    }
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const std::vector<cluster::Cluster*>& clusters) {
    std::vector<math::NumericVector<int>> arCoords;
    arCoords.reserve(clusters.size());
    for (const auto& cluster : clusters) {
        arCoords.push_back(cluster->getCoords());
    }
    stream << arCoords;
    return stream;
}

#endif //MOLECULAR_PRINTER_CLUSTER_H
