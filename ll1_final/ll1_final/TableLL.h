#pragma once
#include "GuideSetsGenerator.h"

class TableLL
{
public:
	TableLL();
	void CreateTable();
	vector <LL> GetLL();
	Rules GetRules();
	unordered_map<string, vector<int>> GetIdxOfRules();

private:
	GuideSetsGenerator _g;
	Rules _rules;
	vector<vector<string>> _predicts;
	vector <LL> ll_tbl;	
	unordered_map<string, int> idx_of_left;
	unordered_map<string, vector<int>> idx_of_rules;


	void ShowLLTable();
	void UpdateEmptyIdx();
	void GetUniquePredicts();
	void GetUniqueHeads();
	void ShowUnique();
	vector<string> _uniqueHeads;
	unordered_map<string, vector<string>> _uniquePredicts;
};


