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
#include <algorithm>
#include "rule.h"
#include "cluster.h"
#include "sim_cell.h"
using namespace std;

void fillRuleList(vector<Rule> &list, const char * rule_file, int offset);
void runMetropolis1(float passes, float temp1, float temp2, float temp_inc, SimCell &sim_cell, vector<Rule> &mc_rules);
void runMetropolis2(float passes, float temp1, float temp2, float temp_inc, vector<Rule> &mc_rules);
float evalLattice(float temp, SimCell &sim_cell, vector<Rule> &MC_rules);
float evalSiteEnergy1(float temp, int site, SimCell &sim_cell, vector<Rule> &MC_rules);
float evalSiteEnergy2(float temp, int site, SimCell &sim_cell, vector<Rule> &MC_rules);
bool compf(float x1, float x2, float eps = 0.000001);
bool compv(vector<float> &x1, vector<float> &x2, float eps = 0.000001);
#endif