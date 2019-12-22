#include "Header.h"

class GuideSetsGenerator
{
private:
	void FindFirsts();
	void UpdateFirst(vector<bool>& fstStatus);

	void FindFollows();
	void UpdateFollows(vector<bool>& flwStatus);
	bool CheckNoTerminalsInFollow(vector<bool>& flwStatus, int pos);

	void GetUniqueSets(vector<vector<string>>);
	bool IsNoTerm(string& lexem);
	void GetUniqueRuleHeads();
	void GetEmpties();

	void FindPredicts();

	Rules _rules;
	unordered_map<string, vector<string>> _uniqueFirstSets;
	vector<string> _uniqueRuleHeads;
	vector<bool> _canBeEmpty;

	vector<vector<string>> _firsts;
	vector<vector<string>> _follows;
	vector<vector<string>> _predicts;


public:
	void FindGuideSets();
	void ShowSet(vector<vector<string>> sets, string setName);
	vector<vector<string>> GetPredicts();
	Rules GetRules();
};

