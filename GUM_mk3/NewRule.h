#pragma once
#ifndef new_rule_h
#define new_rule_h
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class New_Rule {
private: 
	int order;
	string plain;
	string phase;
	int coordination;
	string neighbor_arrangment;
	float energy_contribution;
	//string name; ////////////////////////////////////////////////////////////////////////////////////////////

public:
	string name;
	vector<int> home_species;
	vector<int> neighbor_species;
	vector<float> distances;
	vector<int> spins;
	bool use_spins;
	vector<int> cluster;
	New_Rule(void);
	New_Rule(string _name, float energy_contribution, int _order, string _plain, string _phase, int _coordination, string _neighbor_arrangment, vector<int> _home_species, vector<int> _neighbor_species);
	float getEnergyContribution(void);
	void setEnergyContribution(float input);
	string getPlain();
	int getOrder();
	int getPhase();
	string getNeighborArrangment();
	// need to add atom first... float applyRule()
};

#endif