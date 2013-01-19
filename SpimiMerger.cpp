#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "SpimiMerger.h"

int getDictionarySize(map<string,list<Posting> >& dictionary){
	int toRet=0;
	for(map<string,list<Posting> >::iterator it = dictionary.begin(); it!=dictionary.end();it++){
		toRet++;
	}
	return toRet;
}

	using namespace std;
	const long maxSpace = 10000;
	#define CHAR_SIZE 26
	char include[CHAR_SIZE] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	SpimiMerger::SpimiMerger(){
		currentUsage = 0;
		numOfBlocks = 0;
		numOfTerms=0;
	}
	
	SpimiMerger::SpimiMerger(vector<string> f){
		currentUsage = 0;
		numOfBlocks = 0;
		files = f;
		numOfTerms=0;
	}
	SpimiMerger::~SpimiMerger(){
		//cout<<"=============current usage: "<<currentUsage<<endl;
		//cout<<"=============Number of terms: "<<numOfTerms<<endl;
	}
	
	vector<string> SpimiMerger::mergeFiles(){
		ifstream reader;
		string line = "";
		pair<string,list<Posting> > tempPair;
		for(unsigned int j=0; j<CHAR_SIZE;j++){
			cout << "Merging " << include[j] <<"..." ;
			for(unsigned int i=0; i<files.size();i++){
				const char* filename = files[i].c_str();
				reader.open(filename);
					while(reader.good()){
						getline(reader,line);
						if(line == ""){
							continue;
						}
						if(line[0]>include[j]){
							break;
						}
						if(line[0]<include[j]){
							continue;
						}
						tempPair = br.getKeyValue(line);
						savePair(tempPair);
					}
				reader.close();
			}
			dumpToBlock(include[j]);
			cout << "Done" << endl;
		}
		return blocks;
	}
	string SpimiMerger::finalMerge(){
		ifstream reader;
		string line = "";
		string finalFile = "final_index.txt";
		cout << "Final merging of blocks...";
		const char* tempfinal = finalFile.c_str();
		ofstream writer(tempfinal);
		for(unsigned int i=0; i<blocks.size();i++){
			const char* tempblock = blocks[i].c_str();
			reader.open(tempblock);
			while(reader.good()){
				getline(reader,line);
				if(line!=""){
				writer << line<<endl;
				}
			}
			reader.close();
		}
		writer.close();
		cout << "Done" << endl;
		return finalFile;
	}
	void SpimiMerger::dumpToBlock(char current){
		numOfTerms += getDictionarySize(dictionary);
		string blockFile = "merge/spimi_merge_";
		string extension = ".txt";
		stringstream blockFilename;
		numOfBlocks++;
		blockFilename << blockFile << current << extension;
		blocks.push_back(blockFilename.str());
		list<Posting> tempPostings;
		const char* tempblock = blockFilename.str().c_str();
		ofstream reader(tempblock);
		for(map<string,list<Posting> >::iterator it = dictionary.begin();it != dictionary.end();++it){			
			reader << it->first;
			reader << "#";
			tempPostings = it->second;
			for(list<Posting>::iterator li = tempPostings.begin();li != tempPostings.end();++li){
				reader << li->toBlock();
				reader <<"~";
			}
			reader<<endl;
		}
		dictionary.erase(dictionary.begin(), dictionary.end());
		//currentUsage = 0;
		reader.close();
	}
	list<Posting> mergePair(list<Posting>& lop, list<Posting>& toMerge){
		list<Posting> final;
		list<Posting>::iterator it1 = lop.begin();
		list<Posting>::iterator it2 = toMerge.begin();
		bool done1=false, done2=false, done=false;
		Posting temp;

		while(!done)
		{
			if(it1==lop.end()){
				done1=true;
			}
			if(it2==toMerge.end()){
				done2=true;
			}
			done = done1 && done2;
			if(done){
				continue;
			}
			if(done1 && !done2){
				final.push_back(*it2);
				it2++;
				continue;
			}
			if(!done1 && done2){
				final.push_back(*it1);
				it1++;
				continue;
			}

			if(it1->getDocId() < it2->getDocId())
			{
				final.push_back(*it1);
				it1++;
			}else if(it1->getDocId() > it2->getDocId()){
				final.push_back(*it2);
				it2++;
			}else{
				temp = *it1;
				temp.setFrequency(it1->getFrequency() + it2->getFrequency());
				final.push_back(temp);
				it1++;
				it2++;
			}
		}
		return final;
	}
	void SpimiMerger::savePair(pair<string,list<Posting> > toStore){
		map<string,list<Posting> >::iterator temp;
		list<Posting> toMerge;
		pair<string, list<Posting> > p;
		bool found = false;
		Posting tempPosting;
		list<Posting> postings;

		temp = dictionary.find(toStore.first);
		if(temp==dictionary.end()){
			dictionary.insert(toStore);
			incrementUsage();
		}
		else{
			list<Posting>& lop = temp->second;
			toMerge = toStore.second;
			lop = mergePair(lop, toMerge);
		}

		
	}
	bool SpimiMerger::enoughSpace(){
		if(currentUsage>=maxSpace){
			return false;
		}
		return true;
	}
	const map<string, list<Posting> >& SpimiMerger::getDictionary() {
		return dictionary;
	}

	const vector<string>& SpimiMerger::getFiles() {
		return files;
	}

	void SpimiMerger::setFiles(vector<string> f) {
		this->files = f;
	}

	long SpimiMerger::getCurrentUsage() {
		return currentUsage;
	}

		void SpimiMerger::incrementUsage() {
		this->currentUsage++;
	}
	void SpimiMerger::incrementUsage(long by) {
		this->currentUsage+= by;
	}
	long SpimiMerger::getNumOfBlocks(){
		return numOfBlocks;
	}


