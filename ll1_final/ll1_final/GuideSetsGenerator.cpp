#include "GuideSetsGenerator.h"
#include "GrammarReader.h"

void GuideSetsGenerator::GetUniqueRuleHeads()
{
	//cout << endl;
	//список уникальных левых частей
	//cout << "unique heads: ";
	for (auto head : _rules.leftParts)
	{
		if (find(_uniqueRuleHeads.begin(), _uniqueRuleHeads.end(), head) == _uniqueRuleHeads.end())
		{
			_uniqueRuleHeads.push_back(head);
			//cout << head << " ";
		}
	}
	//cout << endl;
}

void GuideSetsGenerator::GetEmpties()
{
	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		if (find(_rules.rightParts[i].begin(), _rules.rightParts[i].end(), "#") != _rules.rightParts[i].end())
		{
			_canBeEmpty.push_back(true);
		}
		else
			_canBeEmpty.push_back(false);
	}
}

void GuideSetsGenerator::FindPredicts()
{
	vector<string>predict;

	for (size_t i = 0; i < _firsts.size(); i++)
	{
		bool haveEmpty = false;

		for (size_t j = 0; j < _firsts[i].size(); j++)
		{
			if (_firsts[i][j] != "#")
			{
				predict.push_back(_firsts[i][j]);
			}
			else
				haveEmpty = true;
		}

		if (haveEmpty)
		{
			for (size_t k = 0; k < _follows[i].size(); k++)
			{
				predict.push_back(_follows[i][k]);
			}
		}

		_predicts.push_back(predict);
		predict.clear();
	}
}

void GuideSetsGenerator::FindGuideSets()
{
	GrammarReader gr;
	gr.ReadGrammarFromFile();
	gr.ShowGrammar();

	_rules = gr.GetRules();
	GetUniqueRuleHeads();
	GetEmpties();
	FindFirsts();
	ShowSet(_firsts, "-----firsts-----");
	FindFollows();
	ShowSet(_follows, "-----follows-----");
	FindPredicts();
	ShowSet(_predicts, "-----predicts-----");
}

void GuideSetsGenerator::FindFirsts()
{
	//первый проход в поисках _firsts
	vector<string> fst;
	vector<bool>fstStatus;
	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		fstStatus.push_back(true);
	}


	for (size_t j = 0; j < _rules.leftParts.size(); j++)
	{
		fst.push_back(_rules.rightParts[j][0]);
		if (IsNoTerm(_rules.rightParts[j][0]))
			fstStatus[j] = false;
		_firsts.push_back(fst);
		fst.clear();
	}	

	GetUniqueSets(_firsts);

	//show unique sets map
/*	for (auto r : _uniqueFirstSets)
	{
		cout << r.first << " :: ";
		for (auto e : r.second)
			cout << e << " ";
		cout << endl;
	}
*/
	UpdateFirst(fstStatus);
}


void GuideSetsGenerator::FindFollows()
{
	vector<bool> flwStatus;
	vector<string>flw;

	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		flwStatus.push_back(true);
	}

	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		if (_rules.leftParts[i] == _rules.startNoTerminal)
			flw.push_back("$");

		for (size_t j = 0; j < _rules.rightParts.size(); j++)
		{
			auto it = find(_rules.rightParts[j].begin(), _rules.rightParts[j].end(), _rules.leftParts[i]);
			if (it != _rules.rightParts[j].end())
			{
				auto index = distance(_rules.rightParts[j].begin(), it);
				if (index != 0)
				{
					if (index != _rules.rightParts[j].size() - 1)
					{
						auto l_it = find(_rules.leftParts.begin(), _rules.leftParts.end(), _rules.rightParts[j][index+1]);
						if (l_it != _rules.leftParts.end())
						{
							for (size_t m = 0; m < _rules.leftParts.size(); m++)
							{
								if (_rules.rightParts[j][index+1] == _rules.leftParts[m])
									for (auto r : _firsts[m])
									{
										if (r != "#")
										{
											flw.push_back(r);
											flwStatus[i] = false;
										}
										else
											flw.push_back(_rules.leftParts[m]);
									}
							}
						}
						else
						{
							flw.push_back(_rules.rightParts[j][index + 1]);
						}
					}
					else
					{
						if (_rules.leftParts[i] != _rules.leftParts[j])
						{
							flw.push_back(_rules.leftParts[j]);
							flwStatus[i] = false;
						}
					}
				}
				//----------------------------------
				else
				{
					if (_rules.rightParts[j].size()== 1)
					{
						flw.push_back(_rules.leftParts[j]);
						flwStatus[i] = false;
					}
				}
				//-----------------------------------
			}
		}
		_follows.push_back(flw);
		flw.clear();
	}

	/*
	cout << "flw status: ";
	for (auto st : flwStatus)
	{
		cout << st << " ";
	}
	cout << endl;
	*/

	cout << "---------------------------" << endl;
	for (size_t i = 0; i < _follows.size(); i++)
	{
		cout << _rules.leftParts[i] << ": ";
		for (auto n : _follows[i])
			cout << n << " ";
		cout << endl;
	}

	UpdateFollows(flwStatus);

}


void GuideSetsGenerator::UpdateFollows(vector<bool>& flwStatus)
{
	while (find(flwStatus.begin(), flwStatus.end(), false) != flwStatus.end())
	{
		/*
		cout << "flw status: ";
		for (auto st : flwStatus)
		{
			cout << st << " ";
		}
		cout << endl;
		*/
		for (size_t pos = 0; pos < flwStatus.size(); pos++)
		{
			if (flwStatus[pos] == true)
			{
				//cout << "Replace " << _rules.leftParts[pos] << endl;
				for (auto i = 0; i < _follows.size(); i++)
				{
					auto n_it = find(_follows[i].begin(), _follows[i].end(), _rules.leftParts[pos]);
					if (n_it != _follows[i].end())
					{
						auto n_pos = distance(_follows[i].begin(), n_it);
						_follows[i].erase(_follows[i].begin() + n_pos);
						for (size_t k = 0; k < _follows[pos].size(); k++)
						{
							_follows[i].push_back(_follows[pos][k]);
						}
						//cout << "now flw in" << _rules.leftParts[i] << "=";
						//for (auto re : _follows[i])
							//cout << re + " ";
						//cout << endl;
						
						if (CheckNoTerminalsInFollow(flwStatus, i))
							flwStatus[i] = true;
					}
				}
			}
			else
			{
				break;
			}
			
		}
	}
}


bool GuideSetsGenerator::CheckNoTerminalsInFollow(vector<bool>& flwStatus, int pos)
{
	bool state = true;
	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		if (find(_follows[pos].begin(), _follows[pos].end(), _rules.leftParts[i]) != _follows[pos].end())
			return false;
	}
	return state;
}


void GuideSetsGenerator::GetUniqueSets(vector<vector<string>> setss)
{
	vector<string> uniqFst;

	for (auto head : _uniqueRuleHeads)
	{
		for (size_t i = 0; i < _rules.leftParts.size(); i++)
		{
			if (_rules.leftParts[i] == head)
			{
				for (size_t k = 0; k < _firsts[i].size(); k++)
				{
					uniqFst.push_back(_firsts[i][k]);
				}
			}
		}
		_uniqueFirstSets.insert(pair<string, vector<string>>(head, uniqFst));
		uniqFst.clear();
	}
}

//Повторный проход по first с целью удаления нетерминалов
void GuideSetsGenerator::UpdateFirst(vector<bool> &fstStatus)
{
	while (true)
	{
		auto it = find(fstStatus.begin(), fstStatus.end(), false);
		if (it != fstStatus.end())
		{
			auto pos = distance(fstStatus.begin(), it);
			for (size_t lexem = 0; lexem < _firsts[pos].size(); lexem++)
			{
				int nt = 0;
				if (IsNoTerm(_firsts[pos][lexem]))
				{
					for (size_t i = 0; i < _rules.leftParts.size(); i++)
					{
						if (_rules.leftParts[i] == _firsts[pos][lexem])
						{
							for (auto f : _firsts[i])
							{
								_firsts[pos].push_back(f);
							}
						}
					}
					_firsts[pos].erase(_firsts[pos].begin() + lexem);
				}
				else
				{
					fstStatus[pos] = true;
				}
			}
		}
		else
		{
			break;
		}
	}
}

bool GuideSetsGenerator::IsNoTerm(string &lexem)
{
	if (find(_uniqueRuleHeads.begin(), _uniqueRuleHeads.end(), lexem) != _uniqueRuleHeads.end())
		return true;
	return false;
}

void GuideSetsGenerator::ShowSet(vector<vector<string>> sets, string setName)
{
	cout << endl;
	cout << setName << endl;
	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		cout << _rules.leftParts[i] << ":  ";
		for (size_t k = 0; k < sets[i].size(); k++)
		{
			cout << sets[i][k] << " ";
		}
		cout << endl;
	}
}

vector<vector<string>> GuideSetsGenerator::GetPredicts()
{
	return _predicts;
}

Rules GuideSetsGenerator::GetRules()
{
	return _rules;
}
