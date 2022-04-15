#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class TokenFactory {
public:
	void doProcessing(string& original, vector<string>& list, string flag);	// processing make token
	void printlist(vector<string> list);	// print token style string
};