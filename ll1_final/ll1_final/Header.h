#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Rules {
	string startNoTerminal;
	int idxOfStartNoTerminal;
	vector<string> leftParts;
	vector<vector<string>> rightParts;
};

struct ParseLine {
	int num;
	string value;
	vector<string> guideSet;
	bool shift;
	int go_to;
	bool to_stack;
	bool err;
	bool final;
	int rule_num;
	int next_alt;
};


struct LL {
	string value;
	vector<string>set;
	int go_to;
	bool is_left;
	int rule_num;
};

const string FILE_NAME = "grammar.txt";
//const string FILE_NAME = "testGrammar.txt";
//const string FILE_NAME = "g.txt";