#include "NFAtoDFA.h"

void NFAtoDFA::showTable(vector<vector<vector<string>>> list, int spaceSize) {
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

NFAtoDFA::NFAtoDFA(vector<vector<vector<string>>>& t) {
	table = t;
}

void NFAtoDFA::convert() {
	for (int i = 1; i < table.size(); i++) {
		for (int j = 1; j < table[i].size(); j++) {
			int saveCol = 0;
			bool isFind = false;
			bool isNull = false;
			vector<vector<string>> addition;	// 추가될 vector를 정의
			set<string> result;	// 중복 값을 없애기 위한 set 자료구조에 저장

			if (table[i][0].size() == table[i][j].size()) {	// '$'체크
				for (int jj = 0; jj < table[i][0].size(); jj++) {
					if (table[i][0][jj] == "$") isNull = true;
				}
			}

			if (!isNull) {

				int duplicount = 0;
				addition.resize(table[0].size());	// 하나의 행 추가
				int o = 0;
				for (int k = 0; k < table[i][j].size(); k++) {
					if (table[i][j][k] != "$")
						addition[0].push_back(table[i][j][k]);	// input값으로 넣기
				}
				bool isDupli = false;
				int b = 0;
				// 같은 것이 나온다면, 새로 행을 만들지 않음
				for (int a = 0; a < table.size(); a++) {
					if (addition[0].size() == table[a][0].size()) {
						for (b = 0; b < addition[0].size(); b++) {
							if (addition[0][b] == table[a][0][b]) {
								duplicount++;
							}
						}
						if (duplicount == addition[0].size())
							isDupli = true;
					}
					if (isDupli) {
						addition[0].clear();	// 중복되면 입력받은 거 다 비우기
						break;
					}
					duplicount = 0;
				}

				if (addition[0].size() != 0) {	// 입력받은게 비어있으면 이 작업을 하지 않음

					for (int m = 1; m < table[0].size(); m++) { // 찾기 과정
						//cout << "-------------------------가로 값 확인: " << table[0][m][0] << endl;
						saveCol = m;
						for (int n = 0; n < addition[0].size(); n++) {	// 새로 추가 될 것을 넣는다.
							//cout << "현재 저장 값....." << addition[0][n] << endl;
							for (o = 1; o < table.size(); o++) {
								for (int q = 0; q < table[o][0].size(); q++) {
									if (table[o][0][q] == addition[0][n]) {
										for (int ii = 0; ii < table[o][saveCol].size(); ii++) {
											//cout << "들어갈 값: " << table[o][saveCol][ii] << endl;
											if (table[o][saveCol][ii] != "$")
												result.insert(table[o][saveCol][ii]);
										}
										isFind = true;
									}
									if (isFind) break;	// 찾았으면 break
								}
								if (isFind) break;	// 찾았으면 break
							}
							isFind = false;	// 여기는 이후 saveCol이 다음 값으로 바뀌는 과정
						}
						for (auto it = result.begin(); it != result.end(); it++) {
							addition[saveCol].push_back(*it);	// non-terminal index인 saveCol마다 추가
						}
						result.clear();
					}
					isFind = false;

					table.resize(table.size() + 1);	// 테이블 하나의 행 추가를 사이즈 재지정
					table[table.size() - 1] = addition;
					addition.clear();
				}
			}
		}
	}
	cout << "DFA form table(not rename, but can recognize";
	showTable(table, 2);
}
