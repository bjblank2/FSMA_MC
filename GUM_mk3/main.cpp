#include <iostream>
#include <string>
#include "rule.h"
#include "monte_carlo.h"
using namespace std;

SimCell sim_cell;

int main(void) {
	bool use_poscar = true;
	vector<Rule> mc_rules;
	vector<float> dist_list{ 0.0 };
	string input_file = "POSCAR";
	int shape[3] = { 4, 4, 4 };//{4, 4, 4 }{512, 512, 0}; { 9,9,9 }{5832, 5832, 0}; { 20,20,20 }{64000, 64000, 0};
	vector<int> species{ 512, 512, 0 }; //{ 5832, 2916, 2916 };
	cout << shape[0] << ',' << shape[1] << ',' << shape[2] << '\n';
	cout << species[0] << ',' << species[1] << ',' << species[2] << '\n';
	fillRuleList(mc_rules, "Mart_Rules.txt",0);
	fillDistList(dist_list, mc_rules);
	sim_cell.initSimCell(input_file, dist_list, shape, species, 1, string("DEFAULT"), string("MART"), string("RAND"), string("ORDERED"),use_poscar);
  	cout << "Testing" << '\n';
	cout << "begining MC" << '\n';
	//runMetropolis1(10, 1, 50, 1, sim_cell, mc_rules);
	//runMetropolis2(10, 1, 50, 1, mc_rules);
	//runMetropolis3(300, 1000, 10, -5, sim_cell, mc_rules);
	runMetropolis4(300, 1000, 1, -5, sim_cell, mc_rules);
	//runMetropolis5(300, 1000, 1, -5, sim_cell, mc_rules);

	int exit;
	std::cin >> exit;
}