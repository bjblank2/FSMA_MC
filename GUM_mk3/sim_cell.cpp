#include "sim_cell.h"

SimCell::SimCell(void) {
	sim_type = "EMPTY";
}

SimCell::SimCell(string POSCAR_file, int _sup_cell[3], vector<int> &_species_numbs, float _cutoff, string _sim_type, string phase_init, string spin_init, string species_init) {
	sim_type = _sim_type;
	cutoff = _cutoff;
	for (int i = 0; i < _species_numbs.size(); i++) {
		species_types.push_back(i);
		species_numbs.push_back(_species_numbs[i]);
	}
	fillUnitCell(POSCAR_file);
	for (int i = 0; i < 3; i++) {
		sup_cell[i] = _sup_cell[i];
		cell_dim[i] = unit_LC[i] * sup_cell[i];
	}
	vector<vector<float>> _pos_list;
	vector<int> _species_list;
	make_supercell(_pos_list, _species_list);
	fillAtomList(_pos_list, _species_list, phase_init, spin_init, species_init);
}

void SimCell::fillUnitCell(string POSCAR_file) {
	ifstream POS_list;
	string pos_line;
	vector<string> pos_lines;
	vector<string> LCs;
	vector<string> pos_list_s;
	vector<vector<float>> pos_list_f;
	vector<int> species_list;
	vector<float> pos{ 0,0,0 };

	POS_list.open(POSCAR_file);
	if (POS_list.is_open()) {
		while (getline(POS_list, pos_line))
		{
			pos_lines.push_back(pos_line);
		}
		POS_list.close();
	}
	else cout << "Unable to open file";
	for (int i = 2; i < 5; i++) {
		pos_line = pos_lines[i];
		LCs = split(pos_line, " ");
		unit_LC[i - 2] = stof(LCs[i - 2]);
	}
	for (int i = 8; i < pos_lines.size(); i++) {
		pos_line = pos_lines[i];
		pos_list_s = split(pos_line, " ");
		for (int j = 0; j < 3; j++) {
			pos[j] = stof(pos_list_s[j]);
		}
		pos_list_f.push_back(pos);
	}
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

void SimCell::make_supercell(vector<vector<float>> &_pos_list, vector<int> &_species_list) {
	int x = sup_cell[0];
	int y = sup_cell[1];
	int z = sup_cell[2];
	int current_cell[3];
	vector<float> new_atom_pos{0,0,0};
	const int unit_length = unit_cell.size();
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				current_cell[0] = i;
				current_cell[1] = j;
				current_cell[2] = k;
				for (int m = 0; m < unit_length; m++) {
					for (int n = 0; n < 3; n++) {
						new_atom_pos[n] = unit_cell[m].pos[n] + current_cell[n] * unit_LC[n];
					}
					_pos_list.push_back(new_atom_pos);
					_species_list.push_back(unit_cell[m].getSpecies());
				}
			}
		}
	}
}

void SimCell::setNeighborDists() {
	float pos1[3];
	float pos2[3];
	float distXYZ[3];
	float dist;
	for (int i = 0; i < atom_list.size(); i++) {
		pos1[0] = atom_list[i].pos[0];
		pos1[1] = atom_list[i].pos[1];
		pos1[2] = atom_list[i].pos[2];
		for (int j = 0; j < atom_list.size(); j++) {
			pos2[0] = atom_list[j].pos[0];
			pos2[1] = atom_list[j].pos[1];
			pos2[2] = atom_list[j].pos[2];
			distXYZ[0] = pos1[0] - pos2[0];
			distXYZ[1] = pos1[1] - pos2[1];
			distXYZ[2] = pos1[2] - pos2[2];
			for (int k = 0; k < 3; k++) {
				if (distXYZ[k] > .5*cell_dim[k]) {
					distXYZ[k] = cell_dim[k] - distXYZ[k];
				}
				else if (distXYZ[k] < -.5*cell_dim[k]) {///////////////////////////////////////////////
					distXYZ[k] = distXYZ[k] + cell_dim[k];
				}
				else if (distXYZ[k] >= -cell_dim[k] & distXYZ[k] <= cell_dim[k]) {
					distXYZ[k] = abs(distXYZ[k]);
				}
				else cout << "ERROR in dist calc";
			}
			dist = sqrt(pow(distXYZ[0], 2) + pow(distXYZ[1], 2) + pow(distXYZ[2], 2));
			if (dist <= cutoff) {
				atom_list[i].neighbor_dists.push_back(dist);
				atom_list[i].neighbors.push_back(j);
			}
		}
	}
}

void SimCell::fillAtomList(vector<vector<float>> &_pos_list, vector<int> &_species_list, string phase_init, string spin_init, string species_init) {
	int atom_index = 0;
	int spin;
	int phase = 0; /////////////////////////////////// place holder
	double spin_rand;
	int index_rand;
	bool use_rand = false;
	vector<int> species_list;
	std::mt19937_64 rng;
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	std::uniform_real_distribution<double> unif(0, 1);

	for (int i = 0; i < _pos_list.size(); i++) {
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
		atom_list.push_back(Atom(i, _species_list[i], spin, phase, _pos_list[i]));
	}
	numb_atoms = atom_list.size();
	std::mt19937_64 rng_int;
	uint64_t timeSeed_int = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss_int{ uint32_t(timeSeed_int & 0xffffffff), uint32_t(timeSeed_int >> 32) };
	rng_int.seed(ss_int);
	std::uniform_int_distribution<int> unif_int(0, numb_atoms - 1);
	if (species_init == "RAND" || use_rand == true) {
		int numb_comp = 0;
		while (numb_comp < species_numbs[2]) {
			index_rand = unif_int(rng_int);
			if (atom_list[index_rand].getSpecies() != 0) {
				if (atom_list[index_rand].getSpecies() != 2) {
					atom_list[index_rand].setSpecies(2);
					numb_comp += 1;
				}
			}
		}
	}
	setNeighborDists();
}

float SimCell::findAtomDists(int atom1, int atom2) {
	auto it = std::find(atom_list[atom1].neighbors.begin(), atom_list[atom1].neighbors.end(), atom2);
	return distance(atom_list[atom1].neighbors.begin(), it);
}

void SimCell::initSimCell(string POSCAR_file, int _sup_cell[3], vector<int> &_species_numbs, float _cutoff, string _sim_type, string phase_init, string spin_init, string species_init) {
	sim_type = _sim_type;
	cutoff = _cutoff;
	for (int i = 0; i < _species_numbs.size(); i++) {
		species_types.push_back(i);
		species_numbs.push_back(_species_numbs[i]);
	}
	fillUnitCell(POSCAR_file);
	for (int i = 0; i < 3; i++) {
		sup_cell[i] = _sup_cell[i];
		cell_dim[i] = unit_LC[i] * sup_cell[i];
	}
	vector<vector<float>> _pos_list;
	vector<int> _species_list;
	make_supercell(_pos_list, _species_list);
	fillAtomList(_pos_list, _species_list, phase_init, spin_init, species_init);
}

SimCell::Atom::Atom(void) {
	species = 10;
	spin = 10;
	phase = 10;
	index = 10;
	cluster_status = "unknown";
}

SimCell::Atom::Atom(int _index, int _species, int _spin, int _phase, vector<float> _pos) {
	index = _index;
	species = _species;
	spin = _spin;
	phase = _phase;
	pos[0] = _pos[0];
	pos[1] = _pos[1];
	pos[2] = _pos[2];
	cluster_status = "unknown";
}

int SimCell::Atom::getNeighborSpin(int _neighbor, SimCell &sim_cell) {
	int neighbor_index = neighbors[_neighbor];
	int neighbor_spin = sim_cell.atom_list[neighbor_index].getSpin();
	return neighbor_spin;
}

int SimCell::Atom::getNeighborSpecies(int _neighbor, SimCell &sim_cell) {
	int neighbor_index = neighbors[_neighbor];
	int neighbor_species = sim_cell.atom_list[neighbor_index].getSpecies();
	return neighbor_species;
}

int SimCell::Atom::getNeighborPhase(int _neighbor, SimCell &sim_cell) {
	int neighbor_index = neighbors[_neighbor];
	int neighbor_phase = sim_cell.atom_list[neighbor_index].getPhase();
	return neighbor_phase;
}

int SimCell::Atom::getNeighborIndex(int _neighbor, SimCell &sim_cell) {
	return neighbors[_neighbor];
}

float SimCell::Atom::getNeighborDist(int _neighbor, SimCell &sim_cell) {
	return neighbor_dists[_neighbor];
}

int SimCell::Atom::getNumbNeighbors(int _site, SimCell &sim_cell) {
	return sim_cell.atom_list[_site].neighbors.size();
}

int SimCell::Atom::getSpin(void) {
	return spin;
}

int SimCell::Atom::getSpecies(void) {
	return species;
}

int SimCell::Atom::getPhase(void) {
	return phase;
}

void SimCell::Atom::setSpin(int _spin) {
	spin = _spin;
}

void SimCell::Atom::setSpecies(int _species) {
	species = _species;
}

void SimCell::Atom::setPhase(int _phase) {
	phase = _phase;
}