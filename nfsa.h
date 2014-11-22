#ifndef NFSA_INCLUDE
#define NFSA_INCLUDE

#include "fsa.h"
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class nfsa : public fsa{
public:
	nfsa(map<char,int>& alphabet, vector<vector<vector<int> > >& transitions, vector<bool>& final);
	map<int, set<int> > eClosureMap;
	map<set<int>, set<int> > eClosureSetMap;
	set<int> eClosure(int state);
	set<int> eClosure(set<int> &states);
};

#endif