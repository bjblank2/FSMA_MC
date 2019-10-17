#include "sim_cell.h"

SimCell::SimCell(void) {
	sim_type = "EMPTY";
}

SimCell::SimCell(const char * POSCAR_file, int _sup_cell[3], vector<int> &_species_numbs, string _sim_type, string phase_init, string spin_init, string species_init) {
	sim_type = _sim_type;
	for (int i = 0; i < _species_numbs.size(); i++) {
		species_types.push_back(i);
		species_numbs.push_back(_species_numbs[i]);
	}
	fillUnitCell(POSCAR_file);
	for (int i = 0; i < 3; i++) {
		sup_cell[i] = _sup_cell[i];
		cell_dim[i] = unit_LC[i] * sup_cell[i];
	}
	vector<float[3]> _pos_list;
	vector<int> _species_list;
	make_supercell(_pos_list, _species_list);
	fillAtomList(
}

void SimCell::fillUnitCell(const char * POSCAR_file) {
	ifstream POS_list;
	string pos_line;
	vector<string> pos_lines;
	vector<string> LCs;
	vector<string> pos_list_s;
	vector<float[3]> pos_list_f;
	vector<int> species_list;
	float pos[3];

	POS_list.open(POSCAR_file);
	if (POS_list.is_open()) {
		while (getline(POS_list, pos_line))
		{
			pos_lines.push_back(pos_line);
		}
		POS_list.close();
		for (int i = 2; i < 5; i++) {
			pos_line = pos_lines[i];
			LCs = split(pos_line, " ");
			unit_LC[i - 2] = stof(LCs[i - 2]);
		}
		for (int i = 7; i > pos_lines.size(); i++) {
			pos_line = pos_lines[i];
			pos_list_s = split(pos_line, " ");
			for (int j = 0; j < 3; j++) {
				pos[j] = stof(pos_list_s[j]);
				pos_list_f.push_back(pos);
			}
		}
	}
	else cout << "Unable to open file";
	X_num = stoi(split(pos_lines[6], " ")[0]);
	for (int i = 0; i < pos_list_f.size(); i++) {
		if (i < X_num) {
			species_list.push_back(0);
		}
		else species_list.push_back(1);
	}
	for (int i = 0; i < pos_list_f.size(); i++) {
		unit_cell.push_back(Atom(i, species_list[i], 0, 0, pos_list_f[i]));
	}
}

void SimCell::make_supercell(vector<float[3]> &_pos_list, vector<int> &_species_list) {
	int x = sup_cell[0];
	int y = sup_cell[1];
	int z = sup_cell[2];
	int current_cell[3];
	float new_atom[3];
	const int unit_length = unit_cell.size();
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				current_cell[0] = i;
				current_cell[1] = j;
				current_cell[2] = k;
				for (int m = 0; m < unit_length; m++) {
					for (int n = 0; n < 3; n++) {
						new_atom[n] = unit_cell[m].pos[n] + current_cell[n] * unit_LC[n];
						_pos_list.push_back(new_atom);
						_species_list.push_back(unit_cell[m].getSpecies());
					}
				}
			}
		}
	}
}

void SimCell::fillAtomList(string phase_init, string spin_init, string species_init) {
	int numb_atoms;
	int atom_index = 0;
	int spin;
	int phase = 0; /////////////////////////////////// place holder
	int species;
	double spin_rand;
	int index_rand;
	bool use_rand = false;
	string pos_line;
	vector<int> species_list;
	float pos[3];
	std::mt19937_64 rng;
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	std::uniform_real_distribution<double> unif(0, 1);

	std::mt19937_64 rng_int;
	uint64_t timeSeed_int = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss_int{ uint32_t(timeSeed_int & 0xffffffff), uint32_t(timeSeed_int >> 32) };
	rng_int.seed(ss_int);
	std::uniform_int_distribution<int> unif_int(0, numb_atoms - 1);


	make_supercell(LCf, pos_list_f, species_list);
	// find neighobr distances
	for (int i = 0; i < pos_list_f.size(); i++) {
		for (int j = 0; j < pos_list_f.size(); j++) {

		}
	}
	for (int i = 0; i < pos_list_f.size(); i++) {
		spin_rand = unif(rng);
		if (spin_init == "FM") {
			spin = 1;
		}
		else if (spin_init == "RAND") {
			if (spin_rand >= (.6666666666666666)) { spin = -1; }
			if (spin_rand >= (.3333333333333333) and spin_rand < (.6666666666666666)) { spin = 0; }
			if (spin_rand < (.3333333333333333)) { spin = 1; }
		}
		else if (spin_init == "AFM") {
			spin = 1; ////////////////////////////////////////////////////////////// just a place holder
		}
		atom_list.push_back(Atom(i, species_list[i], spin, phase, pos_list_f[i]));
	}
	if (species_init == "RAND" || use_rand == true) {
		int numb_comp = 0;
		while (numb_comp < numb_species[2]) {
			index_rand = unif_int(rng_int);
			if (atom_list[index_rand].getSpecies() != 0) {
				if (atom_list[index_rand].getSpecies() != 2) {
					atom_list[index_rand].setSpecies(2);
					numb_comp += 1;
				}
			}
		}
	}
	// Set neighbors

}
