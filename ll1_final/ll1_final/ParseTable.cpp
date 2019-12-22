#include "ParseTable.h"

void ParseTable::CreateParseTable()
{
	for (size_t i = 0; i < _ll_tbl.size(); i++)
	{
		ParseLine pl;
		pl.num = i + 1;
		pl.next_alt = 0;
		pl.go_to = _ll_tbl[i].go_to;
		pl.value = _ll_tbl[i].value;
		pl.rule_num = _ll_tbl[i].rule_num;
		CreateShiftColumn(pl, i);
		CreateGuideSetColumn(pl, i);
		CreateErrorColumn(pl, i);
		CreateStackColumn(pl, i);
		CreateFinalColumn(pl, i);
		_parseTbl.push_back(pl);
	}
}

void ParseTable::CreateStackColumn(ParseLine& pl, int i)
{	
	if (_ll_tbl[i].is_left == false)
	{
		if (find(_rules.leftParts.begin(), _rules.leftParts.end(), pl.value) != _rules.leftParts.end())
		{
			auto  tt = find(_rules.rightParts[pl.rule_num - 1].begin(), _rules.rightParts[pl.rule_num - 1].end(), pl.value);
			auto idx = distance(_rules.rightParts[pl.rule_num - 1].begin(), tt);
			if (idx != _rules.rightParts[pl.rule_num - 1].size() - 1)
				pl.to_stack = true;
			else
				pl.to_stack = false;

		}
		else
			pl.to_stack = false;
	}
	else
		pl.to_stack = false;
		
}

void ParseTable::CreateErrorColumn(ParseLine& pl, int i)
{
	if (_ll_tbl[i].is_left == true)
	{
		if (_idxOfRules.at(pl.value).size() == 1)
			pl.err = true;

		else
		{
			int m = i + 1;
			auto it = find(_idxOfRules.at(pl.value).begin(), _idxOfRules.at(pl.value).end(), m);
			if (it != _idxOfRules.at(pl.value).end())
			{
				auto pos = distance(_idxOfRules.at(pl.value).begin(), it);
				if (pos != _idxOfRules.at(pl.value).size() - 1)
				{
					pl.err = false;
					pl.next_alt = _idxOfRules.at(pl.value)[pos + 1];
				}
				else
				{
					pl.err = true;
				}
			}
		}

	}
	else
	{
		pl.err = true;
	}
}

void ParseTable::CreateGuideSetColumn(ParseLine &pl, int i)
{
	if (_ll_tbl[i].set.size() == 0)
	{
		pl.guideSet.push_back(_ll_tbl[i].value);
		//pl.shift = true;
	}
	else
		pl.guideSet = _ll_tbl[i].set;
}

void ParseTable::CreateShiftColumn(ParseLine& pl, int i)
{
	if (_ll_tbl[i].set.size() == 0)
		pl.shift = true;
	else
		pl.shift = false;
}

void ParseTable::CreateFinalColumn(ParseLine& pl, int i)
{
	if (find(pl.guideSet.begin(), pl.guideSet.end(), "$") != pl.guideSet.end())
		pl.final = true;
	else
		pl.final = false;
}

ParseTable::ParseTable()
{
	TableLL ll_table;
	ll_table.CreateTable();
	_ll_tbl = ll_table.GetLL();
	_rules = ll_table.GetRules();
	_idxOfRules = ll_table.GetIdxOfRules();
	//CreateParseTable();
}

void ParseTable::ShowParseTable()
{
	//CreateParseTable();
	cout << endl;
	cout << setw(4) << left << "NUM";
	cout << setw(4) << left << "NT";
	cout << setw(10) << left << "GUIDE_SET";
	cout << setw(8) << left << "SHIFT";
	cout << setw(5) << left << "GOTO";
	cout << setw(8) << left << "STACK";
	cout << setw(8) << left << "ERROR";
	cout << setw(8) << left << "FINAL";
	cout << setw(4) << right << "RULE";
	cout << setw(4) << right << "POS" << endl;
	

	for (auto line : _parseTbl)
	{
		cout << setw(4) << left << line.num;
		cout << setw(4) << left << line.value;

		string gs;
		for (auto e : line.guideSet)
			gs.append(e + " ");
		cout << setw(10) << left << gs;
		cout << setw(8) << left << boolalpha << line.shift;
		cout << setw(5) << left << line.go_to;
		cout << setw(8) << left << boolalpha << line.to_stack;
		cout << setw(8) << left << boolalpha << line.err;
		cout << setw(8) << left << boolalpha << line.final;
		cout << setw(4) << right << line.rule_num;
		cout << setw(4) << right << line.next_alt << endl;
	}
}

vector<ParseLine> ParseTable::GetParseTable()
{
	return _parseTbl;
}


/*
if (_ll_tbl[i].is_left == false)
{
	if (_rules.rightParts[pl.rule_num - 1].size() > 1)
	{
		auto  t_2 = find(_rules.rightParts[pl.rule_num - 1].begin(), _rules.rightParts[pl.rule_num - 1].end(), pl.value);
		auto idx_2 = distance(_rules.rightParts[pl.rule_num - 1].begin(), t_2);

		if (idx_2 != 0)
		{
			auto  t_1 = find(_rules.leftParts.begin(), _rules.leftParts.end(), _rules.rightParts[pl.rule_num - 1][idx_2 - 1]);
			if (t_1 != _rules.leftParts.end())
				pl.to_stack = true;
		}
	}
	else
		pl.to_stack = false;

}
else
	pl.to_stack = false;
*/

/*
		if (_ll_tbl[i].is_left == true)
		{
			if (_idxOfRules.at(pl.value).size() == 1)
				pl.err = true;

			else
			{
				int m = i + 1;
				auto it = find(_idxOfRules.at(pl.value).begin(), _idxOfRules.at(pl.value).end(), m);
				if (it != _idxOfRules.at(pl.value).end())
				{
					auto pos = distance(_idxOfRules.at(pl.value).begin(), it);
					if (pos != _idxOfRules.at(pl.value).size()-1)
						pl.err = false;
					else pl.err = true;
				}
			}

		}
		else
		{
			pl.err = true;

			if (find(_rules.leftParts.begin(), _rules.leftParts.end(), pl.value) != _rules.leftParts.end())
			{
				auto  tt = find(_rules.rightParts[pl.rule_num - 1].begin(), _rules.rightParts[pl.rule_num - 1].end(), pl.value);
				auto idx = distance(_rules.rightParts[pl.rule_num - 1].begin(), tt);
				if (idx != _rules.rightParts[pl.rule_num - 1].size() - 1)
					pl.to_stack = true;
				else
					pl.to_stack = false;

			}

		}
		*/