#include <map>
#include <list>
#include <vector>
#include "BlockReader.h"
#include "Posting.h"
using namespace std;
class SpimiMerger {
private:
	map<string,list<Posting> > dictionary;
	vector<string> files; 
	vector<string> blocks;
	long numOfBlocks;
	long currentUsage;
	long numOfTerms;
	BlockReader br;
	void dumpToBlock(char current);
	void savePair(pair<string,list<Posting> > toSave);
	bool enoughSpace();
	
public:
	SpimiMerger();
	SpimiMerger(vector<string> f);
	~SpimiMerger();
	vector<string> mergeFiles();
	string finalMerge();
	const map<string, list<Posting> >& getDictionary();
	const vector<string>& getFiles();
	void setFiles(vector<string> files);
	long getCurrentUsage();
	void incrementUsage();
	void incrementUsage(long by);
	long getNumOfBlocks();
};
