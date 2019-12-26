#include "ParseTableRunner.h"

int main()
{
	ParseTableRunner ptr;
	ptr.ShowParseTable();

	ifstream fin(INPUT_FILE);
	string inputText;

	cout << "\n------Parsing------" << endl;
	while (getline(fin, inputText))
	{
		cout << setw(15) << left << inputText;
		inputText.append("$");
		vector <int> st;
		int cPointer = 1;
		cout << ptr.ProcessData(inputText, cPointer, st) <<" : "<<inputText<<endl;

	}
	system("pause");
	return 0;
}

