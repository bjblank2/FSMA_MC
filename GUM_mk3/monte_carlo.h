#pragma once
#ifndef mc_h
#define mc_h
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <sstream>
#include "rule.h"
#include "atom.h"
#include "cluster.h"

using namespace std;

int applyBC(int i, int inc, int limit);
void fillRuleList(vector<Rule> &list, const char * rule_file, int offset);
void fillAtomList(vector<Atom> &atom_list, int shape[3], int numb_species[3], string POSCAR_File, string phase_init, string spin_init, string species_init);
void init_calcJK(int site, vector<Atom> &atom_list, vector<Rule> &cluster_rules, vector<Rule> &spin_rules);
void pair_calcJK(int site, int neighbor, vector<Atom> &atom_list, vector<float> J_K); //////////
void re_calcJK(int site, int old_home_spin, vector<Atom> &atom_list, vector<Rule> &cluster_rules, vector<Rule> &spin_rules);
void clacBEGParams(vector<float> &J_K);
float evalCluster(vector<Atom> &atom_list, Cluster &cluster, vector<Rule> &cluster_rules, vector<Rule> &spin_rules, vector<float> &J_K, float temp);
float evalLattice(float temp, vector<Atom> &atom_list, vector<Rule> &MC_rules);
float evalSiteEnergy1(float temp, int site, vector<Atom> &atom_list, vector<Rule> &MC_rules);
void runMetropolis1(float passes, float temp1, float temp2, float temp_inc, vector<Atom> &atom_list, vector<Rule> &MC_rules);