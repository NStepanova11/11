#pragma once
#include "Header.h"
#include "ParseTable.h"

class ParseTableRunner
{	
private: 
	ParseTable _pt;
	vector<ParseLine> _pTbl;
	string GetLexem(string& inputString);
public:
	ParseTableRunner();
	void ShowParseTable();
	bool ProcessData(string& inputString, int& cPointer, vector<int> &st);
};

