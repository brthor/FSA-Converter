#include "fsa.h"

fsa::fsa(){}

fsa::fsa(map<char,int> &alphabet, vector<vector<vector<int> > > &transitions, vector<bool> &final){
	this -> alphabet = alphabet;
	this -> transitions = transitions;
	this -> final = final;
}

bool fsa::validate(string input) {
	return validate_recurse(input,0,0);
}

bool fsa::validate_recurse(string input, int stringPosition, int currentState){
	//Check if we are in a final state and have processed the whole string
	if(final[currentState] && stringPosition >= input.size()) return true;

	//Check if we are over 
	else if(stringPosition >= input.size()) return false;

	//Get the current symbol's representation
	map<char,int>::iterator mit = alphabet.find(input[stringPosition]);

	//check for existence of the symbol in the alphabet
	if(mit == alphabet.end()) return false;

	int symbol = mit->second;

	//If there are no next states, return false, we are in a trap
	if(transitions[currentState][symbol].size() == 0){
	 	return false;
	}

	//For each possible next state, traverse the computation tree to find a valid state
	for(vector<int>::iterator it = transitions[currentState][symbol].begin(); it != transitions[currentState][symbol].end(); ++it){
		if(validate_recurse(input, stringPosition + 1, *it)) return true;
	}

	//No valid branches were found in the computation tree
	return false;
}

 void fsa::printOutput(){

	cout << "(1) ";
	printStates();
	cout << endl;

	cout << "(2) " ;
	printFinalStates();
	cout << endl;

	cout << "(3) ";
	printAlphabet();
	cout << endl;

	cout << "(4) ";
	printTransitionTable();
	cout << endl;


}

 void fsa::printStates() {
	cout << "number of states: " << transitions.size();
}

 void fsa::printFinalStates(){
	cout << "final states: ";

	bool comma = false; int index = 0;
	for(vector<bool>::iterator it = final.begin(); it != final.end(); ++it){
		if(*it){
			if(comma) cout << ", ";
			else comma = true;

			cout << index;
		}
		++index;
	}
}

 void fsa::printAlphabet(){
	cout << "alphabet: ";
	bool comma = false;
	for(map<char,int>::iterator it = alphabet.begin(); it != alphabet.end(); ++it){
		//Don't print empty string as part of alphabet
		if(it->second == 0) continue;

		if(comma) cout << ", ";
		else comma = true;

		cout << it->first;
	}
}

 void fsa::printTransitionTable(){
	cout << "transitions: " << endl;

	//For each state
	for(int stateNumber = 0; stateNumber < transitions.size(); ++stateNumber){
		//For each possible symbol
		for(map<char, int>::iterator it = alphabet.begin(); it != alphabet.end(); ++it){

			int representation = it->second;
			char symbol = it->first;

			//if there are any next states print, else skip
			if(transitions[stateNumber][representation].size() > 0){

				cout << "\t" << stateNumber << " " << symbol;

				//for each next possible state
				for(vector<int>::iterator vit = transitions[stateNumber][representation].begin(); vit != transitions[stateNumber][representation].end(); ++vit){
					cout << " " << *vit;
				}

				cout <<endl;
			}
		}
	}
}