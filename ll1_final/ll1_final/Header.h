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

const int START_RULE = 2;
const string INPUT_FILE = "input.txt";
const string FILE_NAME = "g.txt";

//const string INPUT_FILE = "newInput.txt";
//const string FILE_NAME = "newGrammar.txt";