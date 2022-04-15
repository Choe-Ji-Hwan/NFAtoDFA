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
			vector<vector<string>> addition;	// �߰��� vector�� ����
			set<string> result;	// �ߺ� ���� ���ֱ� ���� set �ڷᱸ���� ����

			if (table[i][0].size() == table[i][j].size()) {	// '$'üũ
				for (int jj = 0; jj < table[i][0].size(); jj++) {
					if (table[i][0][jj] == "$") isNull = true;
				}
			}

			if (!isNull) {

				int duplicount = 0;
				addition.resize(table[0].size());	// �ϳ��� �� �߰�
				int o = 0;
				for (int k = 0; k < table[i][j].size(); k++) {
					if (table[i][j][k] != "$")
						addition[0].push_back(table[i][j][k]);	// input������ �ֱ�
				}
				bool isDupli = false;
				int b = 0;
				// ���� ���� ���´ٸ�, ���� ���� ������ ����
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
						addition[0].clear();	// �ߺ��Ǹ� �Է¹��� �� �� ����
						break;
					}
					duplicount = 0;
				}

				if (addition[0].size() != 0) {	// �Է¹����� ��������� �� �۾��� ���� ����

					for (int m = 1; m < table[0].size(); m++) { // ã�� ����
						//cout << "-------------------------���� �� Ȯ��: " << table[0][m][0] << endl;
						saveCol = m;
						for (int n = 0; n < addition[0].size(); n++) {	// ���� �߰� �� ���� �ִ´�.
							//cout << "���� ���� ��....." << addition[0][n] << endl;
							for (o = 1; o < table.size(); o++) {
								for (int q = 0; q < table[o][0].size(); q++) {
									if (table[o][0][q] == addition[0][n]) {
										for (int ii = 0; ii < table[o][saveCol].size(); ii++) {
											//cout << "�� ��: " << table[o][saveCol][ii] << endl;
											if (table[o][saveCol][ii] != "$")
												result.insert(table[o][saveCol][ii]);
										}
										isFind = true;
									}
									if (isFind) break;	// ã������ break
								}
								if (isFind) break;	// ã������ break
							}
							isFind = false;	// ����� ���� saveCol�� ���� ������ �ٲ�� ����
						}
						for (auto it = result.begin(); it != result.end(); it++) {
							addition[saveCol].push_back(*it);	// non-terminal index�� saveCol���� �߰�
						}
						result.clear();
					}
					isFind = false;

					table.resize(table.size() + 1);	// ���̺� �ϳ��� �� �߰��� ������ ������
					table[table.size() - 1] = addition;
					addition.clear();
				}
			}
		}
	}
	cout << "DFA form table(not rename, but can recognize";
	showTable(table, 2);
}
