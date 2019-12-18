#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Rules {
	string startNoTerminal;
	int idxOfStartNoTerminal;
	vector<string> leftParts;
	vector<vector<string>> rightParts;
};

const string FILE_NAME = "grammar.txt";
//const string FILE_NAME = "testGrammar.txt";
//const string FILE_NAME = "g.txt";