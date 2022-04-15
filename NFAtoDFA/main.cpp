/*
	Maked by Dongguk university 2017112104 choe ji hwan
	It was created on 2021-05-29.
*/
#include <fstream>
#include "NFAtoDFA.h"
using namespace std;

int main() {
	/* You must enter a name for the file. (The only place the client needs to make changes)
	| Change this place.
	|
	| input form here
	-----------------------------------------------------------------------------------------------------------------
	| e.g.)
	| q0 q2									// input non-terminal symbol
	| 0 1									// input terminal symbol
	| q0									// input start non-terminal Symbol
	| q1									// input final non-terminal Symbol
	| q0 0 q0,q1;q0 1 q0;q1 0 $;q1 1 q0,q1;	// input delta-function
	-----------------------------------------------------------------------------------------------------------------
	| Each recognizable character or symbol is separated by a space(' '), 
	| 	and the symbols or functions to be entered in order are separated by Enter('\n').
	| In delta-function, one delta-function is separated by space, and the other delta-function is separated by ';'.
	| A covalent representation, such as null, is written by substituting '$'.
	| If there are multiple arrival symbols, 
	|	separate them by ',' in order, such as 'a,b,c' without space in the third part of each delta-function.
	| ----------------------------------------------------------------------------------------------------------------------
	| ������ �νİ����� ���ڳ� �ɺ��� �����̽�(' ')�� ���еǰ�, ������ ���� �Էµ� �ɺ��̳� functions���� Enter('\n')�� �����Ѵ�.
	| delta-function������ �ϳ��� delta-function���� �����̽��� ���еǰ�, �ٸ� delta-function���� ';'�� ���еȴ�.
	| null�� ���� ������ ǥ���� '$'�� ��ü�ؼ� �ۼ��Ѵ�.
	| ���� �ɺ��� �������� ���, �� delta-function�� ����°���� ���� ���� ������� a,b,có�� ','�� �����Ѵ�.
	*/
	ifstream readfile;
	readfile.open("input.txt");	// The only change part. input file(.txt) name
	int line = 0;

	//	NFA M = { Q(Symbols), Sigma, Delta-function, q0(start-Symbol), Final-Symbol) }
	string symbols;
	string sigmas;
	string startSymbol;
	string finalSymbol;
	string delFuncs;

	vector<string> symbollist;	// symbol list
	vector<string> sigmalist;	// sigma list
	vector<string> finalSymbollist; // final symbol list
	vector<string> deltaFunctions;	// delta-function list

	TokenFactory factory;

	if (readfile.is_open()) {
		while (!readfile.eof()) {

			switch (line++)
			{
			case 0: { getline(readfile, symbols);		break; }
			case 1: { getline(readfile, sigmas);		break; }
			case 2: { getline(readfile, startSymbol);	break; }
			case 3: { getline(readfile, finalSymbol);	break; } 
			case 4: { getline(readfile, delFuncs);		break; }
			}
		}
	}
	readfile.close();

	// check file
	cout << "The program is NfA to DFA\nEntered NFA" << endl;
	cout << "Q(Symbols)" << endl;
	factory.doProcessing(symbols, symbollist, " ");	// make token list
	factory.printlist(symbollist);

	cout << "Sigma(Non-terminal symbols)" << endl;
	factory.doProcessing(sigmas, sigmalist, " ");	// make token list
	factory.printlist(sigmalist);

	cout << "delta-function" << endl;
	factory.doProcessing(delFuncs, deltaFunctions, ";");	// make token list
	factory.printlist(deltaFunctions);

	cout << "Start Symbol" << endl;
	cout << "[ " << startSymbol << " ] " << endl;;	// only one

	cout << "Final Symbol" << endl;
	factory.doProcessing(finalSymbol, finalSymbollist, " ");	// make token list
	factory.printlist(finalSymbollist);

	cout << endl;
	NFA nfa(symbollist, sigmalist, deltaFunctions, startSymbol, finalSymbollist);
	nfa.makeTable();	// make NFA table

	vector<vector<vector<string>>> converttable;
	nfa.getTable(converttable);	// NFA table is input parameter

	NFAtoDFA conv(converttable);	// NFAtoDFA class to convert 
	conv.convert();	// convert
}