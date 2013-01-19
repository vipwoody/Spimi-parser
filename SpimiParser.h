#include <map>
#include <list>
#include "Posting.h"
#include "Tokenizer.h"
using namespace std;
class SpimiParser {
private:
	map<string,list<Posting> > dictionary;
	vector<string> files;
	vector<string> blocks;
	long numOfBlocks;
	long currentUsage;
	long maxSpace;
	Tokenizer tokenizer;
	void dumpToBlock();
	void SpimiSave(vector<string> toStore, Posting posting);
	bool enoughSpace();
	
public:
	SpimiParser();
	SpimiParser(vector<string> f, long space);
	~SpimiParser();
	vector<string> parseFiles();
	const map<string, list<Posting> >& getDictionary() ;
	const vector<string>& getFiles();
	void setFiles(vector<string> files);
	long getCurrentUsage();
	void incrementUsage();
	long getNumOfBlocks();
};
