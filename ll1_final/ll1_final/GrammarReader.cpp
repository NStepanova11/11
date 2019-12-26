#include "GrammarReader.h"

void GrammarReader::ReadGrammarFromFile()
{
	ifstream fin(FILE_NAME);
	string line;
	stringstream ss;
	int lineNum = 0;

	while (getline(fin, line))
	{
		lineNum++; //индекс прочитанной строки

		ss << line;
		vector<string> ruleBody = {};
		string lexem = "";

		string leftNonTerminal;
		ss >> leftNonTerminal;

		//стартовый нетерминал должен находиться в первой строке в файле
		if (lineNum == START_RULE)
			rules.startNoTerminal = leftNonTerminal;

		rules.leftParts.push_back(leftNonTerminal);
		rules.idxOfStartNoTerminal = rules.leftParts.size() - 1;

		while (ss >> lexem)
		{
			if (lexem == "->")
				continue;
			else if (lexem == "|")
			{
				rules.leftParts.push_back(leftNonTerminal);
				rules.rightParts.push_back(ruleBody);
				ruleBody.clear();
			}
			else
				ruleBody.push_back(lexem);
		}
		rules.rightParts.push_back(ruleBody); // тк. последнее правило формируется но после последней лексемы выходит из цикла
		ss.clear();
	}
}

Rules GrammarReader::GetRules()
{
	return rules;
}

void GrammarReader::ShowGrammar()
{
	//cout << "Start noterm is: " << rules.startNoTerminal << endl;
	//cout << "Pos of start noterm is: " << rules.idxOfStartNoTerminal << endl;
	cout << "\n----- RULES -----" << endl;
	for (int i = 0; i < rules.leftParts.size(); i++)
	{
		cout << rules.leftParts[i] << " -> ";
		int n = 0;
		for (auto lexem : rules.rightParts[i])
		{
			cout << " " << lexem;
		}
		cout << endl;
	}
}
