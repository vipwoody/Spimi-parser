#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "Tokenizer.h"
using namespace std;
static bool inBODY = false;

	bool predicate(char c){
		if(c>='a' && c<='z'){
			return false;
		}
		return true;
	}
	bool isStopWord(string word){
		const string arr[] = {"the", "a", "i", "you", "he", "we", "and", "or"
		"to", "from", "by", "it", "my", "yours", "his", "her", "of", "an", "that", "those", 			"these", "they", "them", "are", "is", "was", "be", "am", "will", "some"};

		vector<string> stopWords (arr, arr+sizeof(arr)/sizeof(arr[0]) );

		if(stopWords.end() != find(stopWords.begin(), stopWords.end(), word)){
			return true;
		}
		return false;
	}
	void applyLowerCasing(vector<string>& arr){
		for(unsigned int i=0; i<arr.size();i++){
			std::transform(arr[i].begin(), arr[i].end(), arr[i].begin(), ::tolower);
		}
	}
	void removeNonAlphanumeric(vector<string>& arr){
		for(unsigned int i=0; i<arr.size();i++){
			arr[i].erase(remove_if(arr[i].begin(), arr[i].end(), predicate), arr[i].end());
		}
	}
	
	vector<string> removeStopWords(vector<string>& arr){
		vector<string> toRet;
		for(vector<string>::iterator it = arr.begin(); it!= arr.end(); it++){
			if(!isStopWord(*it)){
				toRet.push_back(*it);
			}
		}
		return toRet;
	}

	void ignoreHTML(string& line){
		string toRet;
		int open = line.find("<BODY>");
		int close = line.find("</BODY>");
		if(string::npos != open){
			inBODY=true;
			line = line.substr(open+6);
		}else	if(string::npos != close){
			inBODY=false;
			line = line.substr(0, close);
		}else	if(inBODY){
			line = line;
		}else if(!inBODY){
			line = "";
		}else{
			cout<<"in else case (ignoreHTML)???";
		}
		//return toRet;
	}

	Tokenizer::Tokenizer(){
		
	}
	Tokenizer::~Tokenizer(){
		
	}
	void Tokenizer::tokenizeLine(string& line, vector<string>& arr){
	  ignoreHTML(line);

		stringstream ss(line);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> toRet(begin, end);
		
		arr = toRet;
		applyLowerCasing(arr);
		removeNonAlphanumeric(arr);
		toRet = removeStopWords(arr);
		//return toRet;
	}
	


