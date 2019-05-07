#include "cluster.h"

Cluster::Cluster(void) {
	continue_growth = true;
	next_seed = 0;
	cluster_list = {};
}

Cluster::Cluster(int _next_seed, bool _continue_growth, vector<int> &_cluster_list) {
	next_seed = _next_seed;
	continue_growth = _continue_growth;
	cluster_list = _cluster_list;
}

bool Cluster::inList(int site) {
	bool status;
	if (std::find(cluster_list.begin(), cluster_list.end(), site) != cluster_list.end()) {
		status = true;
	}
	else {
		status = false;
	}
	return status;
}

int Cluster::clusterSize() {
	return cluster_list.size();
}