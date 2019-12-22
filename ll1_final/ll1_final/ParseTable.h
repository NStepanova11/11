#pragma once
#include "Header.h"
#include "TableLL.h"

class ParseTable
{
private:
	vector<ParseLine> _parseTbl;
	vector <LL> _ll_tbl;
	Rules _rules;
	unordered_map<string, vector<int>> _idxOfRules;
	void CreateStackColumn(ParseLine& pl, int i);
	void CreateErrorColumn(ParseLine& pl, int i);
	void CreateGuideSetColumn(ParseLine &pl, int i);
	void CreateShiftColumn(ParseLine& pl, int i);
	void CreateFinalColumn(ParseLine& pl, int i);
public:
	ParseTable();
	void ShowParseTable();
	vector<ParseLine> GetParseTable();
	void CreateParseTable();
};

