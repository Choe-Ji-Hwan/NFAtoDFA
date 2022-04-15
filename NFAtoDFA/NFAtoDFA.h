#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "NFA.h"
using namespace std;

class NFAtoDFA {
public:
	NFAtoDFA(vector<vector<vector<string>>>& t);	// input NFA table
	void convert();	// NFA table to DFA table (If you look at the table, you can draw enough)
	void showTable(vector<vector<vector<string>>> list, int spaceSize); // show table
private:
	vector<vector<vector<string>>> table;	// continue updating table
};