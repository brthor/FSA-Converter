#ifndef FSA_INCLUDE
#define FSA_INCLUDE

#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class fsa{
public:

	vector<bool> final;
	vector<vector<vector<int> > > transitions;

	map<char, int> alphabet;
	
	fsa(map<char,int>& alphabet, vector<vector<vector<int> > >& transitions, vector<bool>& final);
	fsa();

	bool validate(string);

	 void printOutput();
	 void printStates();
	 void printFinalStates();
	 void printAlphabet();
	 void printTransitionTable();

private:
	bool validate_recurse(string, int, int);
};

#endif