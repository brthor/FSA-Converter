#include "dfsa.h"

void dfsa::printDFSAOutput(){
	cout << "(1) ";
	printStates();
	cout << endl;

	for(int i = 0; i < stateMap.size(); ++i){
		cout << "state " << i << ": {";
		for(set<int>::iterator it = stateMap[i].begin(); it != stateMap[i].end(); ++it){
			cout << *it << " ";
		}
		cout <<"}"<<endl;
	}

	cout << "(2) " ;
	printFinalStates();
	cout << endl;

	cout << "(3) ";
	cout << "transitions: " << endl;

	//For each state
	for(int stateNumber = 0; stateNumber < transitions.size(); ++stateNumber){
		//For each possible symbol
		cout << "state " << stateNumber << ": ";
		bool comma = false;
		for(map<char, int>::iterator it = alphabet.begin(); it != alphabet.end(); ++it){

			int representation = it->second;
			char symbol = it->first;

			//if there are any next states print, else skip
			if(transitions[stateNumber][representation].size() > 0){
				if(comma) cout << ", ";
				else comma = true;
				cout << symbol << " " << transitions[stateNumber][representation][0];
			}
		}
		cout <<endl;
	}
	cout << endl;

}

dfsa::dfsa(nfsa &inFsa){
	this->alphabet = inFsa.alphabet;

	//Size transition table + statemap
	int maxSize = pow(2, inFsa.transitions.size());

	transitions.resize(maxSize);
	stateMap.resize(maxSize);

	for(int i = 0; i < maxSize; ++i) transitions[i].resize(alphabet.size());

	subsetConstruction(inFsa);
}


void dfsa::subsetConstruction(nfsa &inFsa){
	queue<pair<int, set<int> > > q; //dfa state num, state members
	map<set<int>, int> seen;

	//for computing final states, tracks all dfa states in which an nfa state is a member
	map<int, set<int> > oldStateMembership;

	int nfaStateCount = transitions.size();
	int dfaStateCount = 0;

	//Initialize
	int currentState; 
	pair<int, set<int> > top; set<int> current; set<int> next;

	set<int> eq = inFsa.eClosure(0);

	q.push(make_pair(dfaStateCount, eq));
	seen[eq] = dfaStateCount;

	for(set<int>::iterator setIt = eq.begin(); setIt != eq.end(); ++setIt)
		oldStateMembership[*setIt].insert(dfaStateCount);

	stateMap[dfaStateCount++] = eq;

	//Begin iterating
	while(!q.empty()){
		top = q.front(); q.pop();

		currentState = top.first;
		current = top.second;

		//Calculate all possible next states for each symbol, except empty string
		
		for(map<char, int>::iterator it = alphabet.begin(); it != alphabet.end(); ++it){
			if(it->second == 0) continue;
			next.clear();

			for(set<int>::iterator setIt = current.begin(); setIt != current.end(); ++setIt){
				next.insert(inFsa.transitions[*setIt][it->second].begin(), inFsa.transitions[*setIt][it->second].end());
			}

			//If we're not going anywhere, ignore this
			if(next.size() > 0){
				//All Possible next states for this symbol in eq
				eq = inFsa.eClosure(next);

				if(seen.find(eq) == seen.end()){
					q.push(make_pair(dfaStateCount, eq));
					seen[eq] = dfaStateCount;

					for(set<int>::iterator setIt = eq.begin(); setIt != eq.end(); ++setIt)
						oldStateMembership[*setIt].insert(dfaStateCount);

					stateMap[dfaStateCount++] = eq;
				}

				/*DEBUG ASSERTION*/ if(transitions[currentState][it->second].size() > 0) cout << "Bad DFA\n";

				transitions[currentState][it->second].push_back(seen[eq]);
			}
		}
	}
	//resize stuff
	transitions.resize(dfaStateCount);
	stateMap.resize(dfaStateCount);

	//Compute final states
	final.resize(dfaStateCount, false);
	int index = 0;
	for(vector<bool>::iterator it = inFsa.final.begin(); it != inFsa.final.end(); ++it){
		if(*it){
			for(set<int>::iterator setIt = oldStateMembership[index].begin(); setIt != oldStateMembership[index] .end(); ++setIt){
				final[*setIt] = true;
			}
		}
		index++;
	}

	//cout << "STATE COUNT DEBUG = " << dfaStateCount <<endl;
}