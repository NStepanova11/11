#pragma once
#include "Header.h"
#include "ParseTable.h"

class ParseTableRunner
{	
private: 
	ParseTable _pt;
	vector<ParseLine> _pTbl;
public:
	ParseTableRunner();
	void ShowParseTable();
	bool ProcessData(string& inputString, int& cPointer, vector<int> &st);
};

