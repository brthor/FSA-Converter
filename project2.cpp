/* CS 311 Project 2: 
 *		Converting Non-Deterministic Finite State Automatons to Deterministic FSAs
 * 
 * Author: Bryan Thornbury
*/

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <queue>
#include <cmath>

#include "fsa.h"

#include "nfsa.h"

#include "dfsa.h"

#define REP(i,a,b) for(int i = int(a); i <= int(b); ++i)

using namespace std;

void processFsaInput(int count){
	int N = 0, D = 0;
	int f = 0, fi = 0, a = 0, p = 0, q = 0, qi = 0;
	char ai = '0';
	//Get number of states
	cin >> N;

	//Input Number of final states
	cin >> f;
	vector<bool> final(N, false);

	REP(i,0,f-1){
		cin >> fi;
		final[fi] = true;
	}

	//Input number of symbols in alphabet
	cin >> a;

	map<char, int> alphabet;
	//empty string
	alphabet['?'] = 0;

	REP(i,1,a){
		cin >> ai;
		alphabet[ai] = i;
	}

	//Initialize Transition Table
	vector<vector<vector<int> > > transitionTable(N);
	REP(i,0,N-1){
		transitionTable[i].resize(a+1);
	}

	//Input number of Non-Deterministic transitions
	cin >> D;

	REP(i,0,D-1){
		cin >> p;
		cin >> ai;
		cin >> q;

		REP(j,0,q-1){
			cin >> qi;
			transitionTable[p][alphabet[ai]].push_back(qi);
		}
	}

	cout << "Finite State Automaton #" << count + 1 << endl;
	nfsa start(alphabet, transitionTable, final);
	start.printOutput();

	cout << "The Equivalent DFSA by Subset Construction:" <<endl;
	dfsa end(start);
	if(count !=6)
		end.printDFSAOutput();
	else{

		end.printStates();
		cout <<endl;
	}
}

int main() {
	FILE *fp;
	if((fp = freopen("input.txt", "r", stdin)) == NULL){
		cout << "Cannot open input file. Closing.\n";
		return 1;
	}

	//Get number of FSA's
	int totalCount;
	cin >> totalCount;

	for(int i = 0; i < totalCount; i ++){
		processFsaInput(i);
	}

	fclose(fp);
	return 0;
}