#include "Posting.h"
#include <string>
#include <map>
#include <list>
#include <vector>
#include<fstream>
using namespace std;

class QueryManager{
private:
	map<string, list<Posting> > dictionary;
	string invertedIndexLocation;
	bool isLoaded;
	void loadDictionary();
	vector<string> fetchFromFile(const vector<string>& queryArr);
	vector<list<Posting> > fetchPostings(const vector<string>& queryArr, bool fromDictionary);
	list<Posting> mergeResults(vector<list<Posting> >& toMerge);
public:
	QueryManager(string location);
	list<Posting> performQuery(string query, bool fromDictionary);
};
