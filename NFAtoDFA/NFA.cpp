#include "NFA.h"

void NFA::showTable(vector<vector<vector<string>>> list, int spaceSize) {
	cout << endl;
	int k;
	int temp = 0;
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list[i].size(); j++) {
			for (k = 0; k < list[i][j].size(); k++) {
				cout << list[i][j][k] << " ";
			}
			if (k == 3) { temp = 1; }
			for (int n = 0; n <= spaceSize - temp; n++) cout << "\t";
			temp = 0;
		}
		cout << endl;
	}
	cout << endl;
}

NFA::NFA(vector<string>& nsymbol, vector<string>& tsymbol, vector<string>& deltafunc, string s, vector<string>& f) {
	q = nsymbol;
	sigma = tsymbol;
	deltaFunctions = deltafunc;
	start = s;
	final = f;

	table.resize(nsymbol.size() + 1);	// nonterminal 세로축 (정해짐)
	for (int i = 0; i < nsymbol.size() + 1; i++) {
		table[i].resize(tsymbol.size() + 1);	// terminal 가로축 (정해짐)
	}

	table[0][0].push_back("δ");	// 0, 0 위치에는 델타

								// 각 값들은 index가 1부터 시작
	for (int i = 1; i < tsymbol.size() + 1; i++)
		table[0][i].push_back(tsymbol.at(i - 1));	// 가로축
	for (int i = 1; i < nsymbol.size() + 1; i++)
		table[i][0].push_back(nsymbol.at(i - 1));	// 세로축
}

void NFA::makeTable() {
	TokenFactory factory;
	set<string> save;

	for (int i = 0; i < deltaFunctions.size(); i++) {
		vector<string> deltafunction;
		factory.doProcessing(deltaFunctions[i], deltafunction, " ");
		// deltafunction (index 0 = nonterminal, index 1 = terminal, index 2 = nonterminal)

		for (int j = 0; j < table[0].size(); j++) {
			for (int k = 0; k < table[0][j].size(); k++) {
				if (table[0][j].at(k) == deltafunction[1]) {	// 가로축과 nonterminal과 일치, 

					for (int m = 0; m < table.size(); m++) {
						for (int n = 0; n < table[m][0].size(); n++) {
							if (table[m][0].at(n) == deltafunction[0]) {	// 세로축과 terminal과 일치
								vector<string> functionResult;
								factory.doProcessing(deltafunction[2], functionResult, ",");
								// only space size to print
								if (spaceSize < functionResult.size()) spaceSize = functionResult.size();

								for (int o = 0; o < functionResult.size(); o++)
									save.insert(functionResult[o]);	// 중복 방지와 정렬을 위해 set에 저장
							}
						}
						for (set<string>::iterator it = save.begin(); it != save.end(); it++)
							table[m][j].push_back(*it);
						save.clear();
					}
				}
			}

		}
	}
	cout << "NFA form table";
	showTable(table, spaceSize);
}

void NFA::getTable(vector<vector<vector<string>>>& t) {
	t = table;
}


