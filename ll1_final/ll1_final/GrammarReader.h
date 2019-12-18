#include "Header.h"

class GrammarReader
{
private: 
	Rules rules;
public:
	void ReadGrammarFromFile();
	Rules GetRules();
	void ShowGrammar();
};

