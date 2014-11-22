#ifndef DFSA_INCLUDE
#define DFSA_INCLUDE

#include <set>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include "fsa.h"
#include "nfsa.h"

using namespace std;

class dfsa : public fsa {
public:
	//Maps a constructed subset to a new state number. Initial state at 0.
	vector<set<int> > stateMap;

	dfsa(nfsa &inFsa);
	void printDFSAOutput();

private:
	
	void subsetConstruction(nfsa&);
};

#endif