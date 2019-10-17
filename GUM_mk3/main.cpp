#include <iostream>
#include <string>
#include "rule.h"
#include "monte_carlo.h"
using namespace std;

int main(void) {
	vector<Atom> atom_list;
	vector<Rule> MC_rules;
	string input_file = "POSCAR";
	int shape[3] = { 10, 10, 20 };//{ 8,8,16 }; //{ 20,20,40 }; //{ 14,14,18 }; //{ 2,2,4 }; //{ 4,4,8 };
	vector<int> species{ 1000, 750, 250 };//{ 512, 384, 128 }; //{ 8000,8000,0 }; //{ 2744,2744,0 }; //{8,6,2}; //{ 64,48,16 };
	cout << shape[0] << ',' << shape[1] << ',' << shape[2] << '\n';
	cout << species[0] << ',' << species[1] << ',' << species[2] << '\n';
	fillRuleList(MC_rules, "NewRuel.txt",0);
	SimCell sim_cell(input_file, shape, species, string("DEFAULT"), string("MART"), string("RAND"), string("RAND"));
	cout << "Testing" << '\n';
	cout << "begining MC" << '\n';
//	//runMetropolis3(2, 500, 100, 1500, 10, atom_list, cluster_rules, spin_rules);
//	runMetropolis7(500,600,700,10, atom_list, cluster_rules, spin_rules);
//	//runMetropolisISING(1000,1,2010,1, atom_list, cluster_rules, spin_rules);
//	int exit;
//	std::cin >> exit;
}