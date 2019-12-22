#include "ParseTableRunner.h"

ParseTableRunner::ParseTableRunner()
{
	_pt.CreateParseTable();
	_pTbl = _pt.GetParseTable();
}

void ParseTableRunner::ShowParseTable()
{
	_pt.ShowParseTable();
}

bool ParseTableRunner::ProcessData(string &inputString, int &cPointer, vector <int>& st)
{
	//невернно обрабатывается стек из-за разницы индекса (с 0) и номером строк (с 1)
	int currPointer = cPointer - 1;
	
	stringstream ss;
	ss<<inputString[0];
	string lexem;
	ss >> lexem;

	if (find(_pTbl.at(currPointer).guideSet.begin(), _pTbl.at(currPointer).guideSet.end(), lexem) != _pTbl.at(currPointer).guideSet.end())
	{
		if (_pTbl.at(currPointer).value != "#")
			cPointer = _pTbl.at(currPointer).go_to;
		else
		{
			cPointer = st[st.size() - 1];
			st.pop_back();
		}

		if (cPointer == NULL)
		{
			cPointer = st[st.size() - 1];
			st.pop_back();
		}
	}
	
	else
	{
		if (_pTbl.at(currPointer).err == true)
			return false;
		else
			cPointer = _pTbl.at(currPointer).next_alt;
	}
			
	if (_pTbl.at(currPointer).shift == true)
	{
		inputString.erase(inputString.begin());

		if (inputString.size() == 0)
		{
			if (_pTbl.at(currPointer).final == true)
				return true;
		}

	}

	if (_pTbl.at(currPointer).to_stack == true)
		st.push_back(currPointer+1);
		
	cout << "STACK : ";
	for (auto e : st)
		cout << e << ",";
	cout << endl;

	ProcessData(inputString, cPointer, st);

	return false;
}
