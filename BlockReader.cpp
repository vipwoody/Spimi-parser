#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "BlockReader.h"
using namespace std;
	vector<string> splitString(string line, char delimiter){
		vector<string> toRet;
		if (std::string::npos == line.find(delimiter)){
			return toRet;
		}
    string word;
    stringstream stream(line);
    while( getline(stream, word, delimiter) )
		{
			toRet.push_back(word);
		}
		return toRet;
	}
	long stringToLong(string line){
		stringstream str(line);
		long x;
		str >> x;
		return x;
	}
	int stringToInt(string line){
		stringstream str(line);
		int x;
		str >> x;
		return x;
	}
	vector<string> getKey(string line){
		vector<string> toRet = splitString(line, '#');
		return toRet;
	}
	vector<string> getPostings(string line){
		vector<string> toRet = splitString(line, '~');
		return toRet;
	}
	Posting getPostingObj(string line){
		Posting posting;
		vector<string> attr = splitString(line, '&');
		posting.setDocId(stringToLong(attr[0]));
		posting.setFilename(attr[1]);
		posting.setFrequency(stringToInt(attr[2]));
		return posting;
	}
	BlockReader::BlockReader(){
		
	}
	BlockReader::~BlockReader(){
		
	}
	pair<string,list<Posting> > BlockReader::getKeyValue(string line){
		pair<string,list<Posting> > toRet;
		vector<string> result = getKey(line);
		if (result.size() == 0) return toRet;
		toRet.first = result[0];
		result = getPostings(result[1]);
		Posting posting;
		list<Posting> tempList;
		for(int i=0; i<result.size();i++)
		{
			posting = getPostingObj(result[i]);
			tempList.push_back(posting);
			toRet.second = tempList;
		}
		return toRet;
	}
	


