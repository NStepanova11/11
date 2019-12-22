#include "ParseTableRunner.h"

int main()
{
	ParseTableRunner ptr;
	ptr.ShowParseTable();

	ifstream fin("input.txt");
	string inputText;
	while (getline(fin, inputText))
	{
		cout << inputText << ": ";
		inputText.append("$");
		vector <int> st;
		int cPointer = 1;
		cout << ptr.ProcessData(inputText, cPointer, st) << " : "<<inputText<<endl;

	}
	system("pause");
	return 0;
}

