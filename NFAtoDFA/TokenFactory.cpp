#include "TokenFactory.h"

void TokenFactory::doProcessing(string & original, vector<string>& list, string flag) {

	int start = 0;
	int d = original.find(flag);
	while (d != -1) {
		list.push_back(original.substr(start, d - start));
		start = d + 1;
		d = original.find(flag, start);
	}
	list.push_back(original.substr(start, d - start));
	if (list.at(list.size() - 1) == "") list.pop_back();
}

void TokenFactory::printlist(vector<string> list) {
	for (int i = 0; i < list.size(); i++) {
		cout << "[ " << list.at(i) << " ] ";
	}
	cout << endl;
}
