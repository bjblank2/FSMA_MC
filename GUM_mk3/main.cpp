#include <iostream>
#include <string>
#include "rule.h"
#include "monte_carlo.h"
using namespace std;

SimCell sim_cell;

int main(void) {
	vector<Rule> mc_rules;
	vector<float> dist_list{ 0.0 };
	string input_file = "POSCAR";
	int shape[3] = { 4, 4, 4 };//{ 8,8,16 }; //{ 20,20,40 }; //{ 14,14,18 }; //{ 2,2,4 }; //{ 4,4,8 };
	vector<int> species{ 512, 512 , 0 };//{ 512, 384, 128 }; //{ 8000,8000,0 }; //{ 2744,2744,0 }; //{8,6,2}; //{ 64,48,16 };
	cout << shape[0] << ',' << shape[1] << ',' << shape[2] << '\n';
	cout << species[0] << ',' << species[1] << ',' << species[2] << '\n';
	fillRuleList(mc_rules, "Aust_Rules.txt",0);
	fillDistList(dist_list, mc_rules);
	sim_cell.initSimCell(input_file, dist_list, shape, species, 1, string("DEFAULT"), string("AUST"), string("RAND"), string("RAND"));
	cout << "Testing" << '\n';
	cout << "begining MC" << '\n';
	runMetropolis3(10, 1, 50, 1, sim_cell, mc_rules);
	//runMetropolis1(10, 1, 50, 1, sim_cell, mc_rules);
	runMetropolis2(10, 1, 50, 1, mc_rules);

	int exit;
	std::cin >> exit;
}