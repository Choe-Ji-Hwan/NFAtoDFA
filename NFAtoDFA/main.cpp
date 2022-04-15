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
	| 각각의 인식가능한 문자나 심볼은 스페이스(' ')로 구분되고, 순서에 따라서 입력될 심볼이나 functions들은 Enter('\n')로 구분한다.
	| delta-function에서는 하나의 delta-function에서 스페이스로 구분되고, 다른 delta-function과는 ';'로 구분된다.
	| null과 같은 공집합 표현은 '$'로 대체해서 작성한다.
	| 도착 심볼이 여러개일 경우, 각 delta-function의 세번째에서 띄어쓰기 없이 순서대로 a,b,c처럼 ','로 구분한다.
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