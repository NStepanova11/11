#include "TableLL.h"

TableLL::TableLL()
{
	_g.FindGuideSets();
	_rules = _g.GetRules();
	_predicts = _g.GetPredicts();
}

void TableLL::CreateTable()
{
	GetUniqueHeads();
	GetUniquePredicts();
	cout << "\n\n";
	
	for (auto e : _uniqueHeads)
	{
		idx_of_left.insert(pair<string, int>(e, 0));
		idx_of_rules.insert(pair<string, vector<int>>(e, {}));
	}

	int n = 0;
	for (size_t i = 0; i < _rules.leftParts.size(); i++)
	{
		LL ll_head;

		n++;
		cout << setw(4) << left << n << setw(4) << left << _rules.leftParts[i];

		string guideSetString;
		for (size_t p = 0; p < _predicts[i].size(); p++)
		{
			guideSetString.append(_predicts[i][p]+" ");
			ll_head.set.push_back(_predicts[i][p]);
		}
		cout << setw(10) << left << guideSetString;
		cout << setw(4) << right << n + 1 << endl;

		ll_head.value = _rules.leftParts[i];
		ll_head.is_left = true;
		ll_head.go_to = n + 1;
		ll_head.rule_num = i+1;

		if (idx_of_left.at(ll_head.value)==0)
			idx_of_left.at(ll_head.value) = n;

		idx_of_rules.at(ll_head.value).push_back(n);

		ll_tbl.push_back(ll_head);
		
		for (size_t j = 0; j < _rules.rightParts[i].size(); j++)
		{
			LL ll_body;

			n++;
			string lexem = _rules.rightParts[i][j];
			cout << setw(4) << left << n << setw(4) << left << lexem;
			string guideSet;

			int go_to = n + 1;

			if (find(_uniqueHeads.begin(), _uniqueHeads.end(), lexem) != _uniqueHeads.end())
			{
				for (size_t ii = 0; ii < _uniquePredicts.at(lexem).size(); ii++)
				{
					guideSet.append(_uniquePredicts.at(lexem)[ii] + " ");
					ll_body.set.push_back(_uniquePredicts.at(lexem)[ii]);
				}
				go_to = NULL;
				ll_body.go_to = NULL;

			}
			else
			{
				if (lexem == "#")
				{
					for (size_t m = 0; m < _predicts.at(i).size(); m++)
					{
						guideSet.append(_predicts.at(i)[m] + " ");
						ll_body.set.push_back(_predicts.at(i)[m]);
					}
					ll_body.go_to = NULL;
				}
				else if (lexem != "#")
				{		
					cout << " J= " << j << " SIZE-1 = " << _rules.rightParts[i].size() - 1 << endl;
					if (j == _rules.rightParts[i].size() - 1)
						ll_body.go_to = NULL;
					else
						ll_body.go_to = go_to;

				}
			}
			
			cout << setw(10) << left << guideSet;
			cout << setw(4) << right << go_to << endl;

			ll_body.value = lexem;
			ll_body.is_left = false;
			ll_body.rule_num = i + 1;
			ll_tbl.push_back(ll_body);

		}
		cout << "-------------------------------" << endl;
	}
	
	cout << endl;
	for (auto i:idx_of_rules)
	{
		cout << i.first << " : ";
		for (auto ii : i.second)
			cout << ii << ",";
		cout << endl;
	}
	cout << endl;
	cout << endl;
	UpdateEmptyIdx();
	ShowLLTable();
}

void TableLL::ShowLLTable()
{
	int n = 1;
	for (auto l : ll_tbl)
	{
		if (l.is_left == true)
			cout << endl;
		cout << setw(4) << left << n;
		cout << setw(4) << left << l.value;
		string s;
		for (auto el : l.set)
			s.append(el + " ");
		cout << setw(8) << left << s;
		cout << setw(4) << left << l.go_to;
		cout << setw(6) << left << boolalpha <<l.is_left;
		cout << setw(4) << right << l.rule_num << endl;

		n++;
	}
}

void TableLL::UpdateEmptyIdx()
{
	for (auto &e : ll_tbl)
	{
		if (e.go_to == NULL)
		{
			if (find(_uniqueHeads.begin(), _uniqueHeads.end(), e.value) != _uniqueHeads.end())
				e.go_to = idx_of_left.at(e.value);
		}
	}
}



void TableLL::GetUniquePredicts()
{
	vector<string> p;

	for (auto head : _uniqueHeads)
	{
		for (size_t i = 0; i < _rules.leftParts.size(); i++)
		{
			if (_rules.leftParts[i] == head)
			{
				for (size_t k = 0; k < _predicts[i].size(); k++)
				{
					p.push_back(_predicts[i][k]);
				}
			}
		}
		_uniquePredicts.insert(pair<string, vector<string>>(head, p));
		p.clear();
	}
}

void TableLL::GetUniqueHeads()
{
	for (auto head : _rules.leftParts)
	{
		if (find(_uniqueHeads.begin(), _uniqueHeads.end(), head) == _uniqueHeads.end())
		{
			_uniqueHeads.push_back(head);
		}
	}
}

void TableLL::ShowUnique()
{
	cout << "\n\n";
	for (auto r : _uniquePredicts)
	{
		cout << r.first<<": ";
		for (auto k : r.second)
			cout << k << " ";
		cout << endl;
	}
}

vector<LL> TableLL::GetLL()
{
	return ll_tbl;
}

Rules TableLL::GetRules()
{
	return _rules;
}

unordered_map<string, vector<int>> TableLL::GetIdxOfRules()
{
	return idx_of_rules;
}

