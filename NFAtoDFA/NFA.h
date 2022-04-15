#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "TokenFactory.h"
using namespace std;

class NFA {
public:
	NFA(vector<string>& nsymbol, vector<string>& tsymbol,
		vector<string>& deltafunc, string s, vector<string>& f);	// make NFA using factor

	void makeTable();	// make NFA table
	void getTable(vector<vector<vector<string>>>& t); // return NFA table
	void showTable(vector<vector<vector<string>>> list, int spaceSize); // show table

private:
	vector<vector<vector<string>>> table;	// NFA table
	vector<string> q;	// Q (non-terminal symbol)
	vector<string> sigma;	// Sigma (terminal symbol)
	vector<string> deltaFunctions;	// delta-functions
	string start;	// Start Symbol
	vector<string> final;	// Final Symbol

	int spaceSize; // only print
};