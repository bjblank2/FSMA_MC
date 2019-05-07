#pragma once
#ifndef cluster_h
#define cluster_h
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Cluster {
private:
public:
	vector<int> cluster_list;
	bool continue_growth;
	int next_seed;
	Cluster(void);
	Cluster(int _next_seed, bool _continue_growth, vector<int> &_cluster_list);
	bool inList(int site);
	int clusterSize();
};
#endif // !cluster_h
