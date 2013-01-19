#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "SpimiParser.h"
using namespace std;

	SpimiParser::SpimiParser(){
		currentUsage = 0;
		numOfBlocks = 0;
	}

	SpimiParser::SpimiParser(vector<string> f, long space){
		currentUsage = 0;
		numOfBlocks = 0;
		files = f;
		maxSpace = space;
	}
	SpimiParser::~SpimiParser(){

	}
	vector<string> SpimiParser::parseFiles(){
		ifstream reader;
		string line = "";
		vector<string> tempArr;
		for(unsigned int i=0; i<files.size();i++){
			const char* tempfile = files.at(i).c_str();
			reader.open(tempfile);
			cout << "Reading file " << files.at(i) << endl;
			Posting tempPosting = new Posting(files.at(i));
				while(reader.good()){
					getline(reader,line);
					tokenizer.tokenizeLine(line, tempArr);
					SpimiSave(tempArr, tempPosting);
				}
			cout << "Done reading file" << endl;
			reader.close();
		}
		dumpToBlock();
		return blocks;
	}
	void SpimiParser::dumpToBlock(){
		string blockFile = "blocks/spimi_block";
		string extension = ".txt";
		stringstream blockFilename;
		numOfBlocks++;
		cout << "\tDumping to Block " << numOfBlocks <<"..."; 
		blockFilename << blockFile << numOfBlocks << extension;
		blocks.push_back(blockFilename.str());
		list<Posting> tempPostings;
		const char* tempfilename = blockFilename.str().c_str();
		ofstream reader(tempfilename);
		for(map<string,list<Posting> >::iterator it = dictionary.begin();it != dictionary.end();++it){			
			reader << it->first;
			reader << "#";
			tempPostings = it->second;
			for(list<Posting>::iterator 	li = tempPostings.begin();li != tempPostings.end();++li){
				reader << li->toBlock();
				reader <<"~";
			}
			reader<<endl;
		}

		dictionary.erase(dictionary.begin(), dictionary.end());
		//dictionary = new map<string, list<Posting> >();
		currentUsage = 0;
		reader.close();
		cout << "Done" << endl;
	}

	void SpimiParser::SpimiSave(vector<string> toStore, Posting posting){
		map<string,list<Posting> >::iterator temp;
		//list<Posting> lop;
		bool found = false;
		for(unsigned int i=0; i<toStore.size();i++){
			if(enoughSpace()){
				temp = dictionary.find(toStore.at(i));
				if(temp==dictionary.end()){
					list<Posting> postings;
					postings.push_back(posting);
					pair<string, list<Posting> > p(toStore.at(i), postings);
					dictionary.insert(p);
					incrementUsage();
				}
				else{
					list<Posting>& lop = (*temp).second;
					for(list<Posting>::iterator it=lop.begin();it!=lop.end();it++){
						if((*it).Equals(posting)){
							found= true;
							(*it).addFrequency();
						}
					}
					if(!found){
						lop.push_back(posting);
						incrementUsage();
					}
				}
			}
			else{
				dumpToBlock();
			}
		}
	}

	bool SpimiParser::enoughSpace(){
		if(currentUsage>=maxSpace){
			return false;
		}
		return true;
	}
	const map<string, list<Posting> >& SpimiParser::getDictionary() {
		return dictionary;
	}

	const vector<string>& SpimiParser::getFiles() {
		return files;
	}

	void SpimiParser::setFiles(vector<string> f) {
		this->files = f;
	}

	long SpimiParser::getCurrentUsage() {
		return currentUsage;
	}

	void SpimiParser::incrementUsage() {
		this->currentUsage++;
	}
	long SpimiParser::getNumOfBlocks(){
		return numOfBlocks;
	}


