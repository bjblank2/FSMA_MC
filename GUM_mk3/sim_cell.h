#pragma once
#pragma once
#ifndef sim_cell_h
#define sim_cell_h
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "atom.h"
#include "file_io.h"
using namespace std;


class SimCell {
public:
	string sim_type;
	vector<Atom> atom_list;
	vector<int> species_types;
	vector<int> species_numbs;
	int sup_cell[3];
	float cell_dim[3];
	int numb_atoms;
	int numb_cells[3];
	vector<Atom> unit_cell;
	float unit_LC[3];
	int X_num;

	SimCell(void);
	SimCell(const char * POSCAR_file, int _sup_cell[3], vector<int> &_species_numbs, string _sim_type, string phase_init, string spin_init, string species_init);
	void fillUnitCell(const char * POSCAR_file);
	void fillAtomList(string phase_init, string spin_init, string species_init);
	void make_supercell(vector<float[3]> &_pos_list, vector<int> &_species_list);
	};
#endif // !sim_cell_h
