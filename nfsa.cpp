#include "nfsa.h"

nfsa::nfsa(map<char,int>& alphabet, vector<vector<vector<int> > >& transitions, vector<bool>& final) 
: fsa(alphabet,transitions,final) {}

//Alphabet 0 is always interpreted as empty string
//Simple BFS through state space
set<int> nfsa::eClosure(int state){

	if(eClosureMap.find(state) != eClosureMap.end()) return eClosureMap[state];

	set<int> closure;
	int current;

	queue<int> q;

	q.push(state);

	while(!q.empty()){
		current = q.front(); q.pop();

		if(closure.find(current) != closure.end()) continue;

		closure.insert(current);

		for(vector<int>::iterator it = transitions[current][0].begin(); it != transitions[current][0].end(); ++it)
			if(closure.find(*it) == closure.end()) q.push(*it);
	}
	
	return closure;
}

set<int> nfsa::eClosure(set<int> &states){

	if(eClosureSetMap.find(states) != eClosureSetMap.end()) return eClosureSetMap[states];

	set<int> closure;

	for(set<int>::iterator it = states.begin(); it != states.end(); ++it){
		set<int> temp = eClosure(*it);
		closure.insert(temp.begin(), temp.end());
	}

	return (eClosureSetMap[states] = closure);
}
