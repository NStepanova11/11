#include "ParseTableRunner.h"

string ParseTableRunner::GetLexem(string& inputString)
{
	stringstream ss;
	ss << inputString[0];
	string lexem;
	ss >> lexem;

	return lexem;
}

ParseTableRunner::ParseTableRunner()
{
	_pt.CreateParseTable();
	_pTbl = _pt.GetParseTable();
}

void ParseTableRunner::ShowParseTable()
{
	cout << "------Parse Table------" << endl;
	_pt.ShowParseTable();
}

bool ParseTableRunner::ProcessData(string& inputString, int& cPointer, vector <int>& st)
{
	while (true)
	{
		/*
		cout << cPointer <<")  " << inputString << "  ST: [";
		if (st.empty() == false)
		{
			for (auto e : st)
				cout << e << " ";
		}
		*/

			int currPointer = cPointer - 1;

			stringstream ss;
			ss << inputString[0];
			string lexem;
			ss >> lexem;

			if (_pTbl.at(currPointer).final == true && st.empty() == true && lexem == "$")
				return true;
			else
			{
				auto it = find(_pTbl.at(currPointer).guideSet.begin(), _pTbl.at(currPointer).guideSet.end(), lexem);
				if (it != _pTbl.at(currPointer).guideSet.end())
				{
					cPointer = _pTbl.at(currPointer).go_to;
					if (cPointer == NULL)
					{
						if (st.empty() == false)
						{
							cPointer = st[st.size() - 1];
							st.pop_back();
						}
						else
							return false;
					}
					//cout << "]  Go to: " << cPointer;
					//cout << endl;
					if (_pTbl.at(currPointer).shift == true)
					{
						if (inputString.size() != 0)
						{
							inputString.erase(inputString.begin());
						}
					}

					if (_pTbl.at(currPointer).to_stack == true)
						st.push_back(currPointer + 2);
				}
				else
				{
					if (_pTbl.at(currPointer).err == false)
						cPointer = _pTbl.at(currPointer).next_alt;
					else return false;
				}

			}
	}
}

/*
bool ParseTableRunner::ProcessData(string& inputString, int& cPointer, vector <int>& st)
{
	while (true)
	{

		cout << " STR: " << inputString<< " CUR Pointer: " << cPointer << " STACK IS: ";
		if (st.empty() == false)
		{
			for (auto e : st)
				cout << e << ", ";
		}
		cout << endl;
		
		
		int currPointer = cPointer - 1;

		stringstream ss;
		ss << inputString[0];
		string lexem;
		ss >> lexem;

		if (_pTbl.at(currPointer).final == true && st.empty() == true && lexem == "$")
			return true;
		else
		{
			auto it = find(_pTbl.at(currPointer).guideSet.begin(), _pTbl.at(currPointer).guideSet.end(), lexem);
			if (it != _pTbl.at(currPointer).guideSet.end())
			{
				cPointer = _pTbl.at(currPointer).go_to;
				if (cPointer == NULL)
				{
					if (st.empty() == false)
					{
						cPointer = st[st.size() - 1];
						st.pop_back();
					}
					else
						return false;
				}

				if (_pTbl.at(currPointer).shift == true)
				{
					if (inputString.size() != 0)
					{
						inputString.erase(inputString.begin());
					}
				}

				if (_pTbl.at(currPointer).to_stack == true)
					st.push_back(currPointer + 2);
			}
			else
			{
				if (_pTbl.at(currPointer).err == false)
					cPointer = _pTbl.at(currPointer).next_alt;
				else return false;
			}

		}
	}
}
*/