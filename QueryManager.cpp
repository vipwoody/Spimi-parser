#include "QueryManager.h"
#include "BlockReader.h"
using namespace std;


vector<string> splitQuery(string line, char delimiter){
	string word;
	stringstream stream(line);
	vector<string> toRet;
	while( getline(stream, word, delimiter) )
	{
		toRet.push_back(word);
	}
	return toRet;
}

vector<list<Posting> > QueryManager::fetchPostings(const vector<string>& queryArr, bool fromDictionary){
	vector<list<Posting> > toRet;
	
	if(fromDictionary){
		map<string,list<Posting> >::iterator temp;
		for (unsigned int i=0; i<queryArr.size();i++){
			temp = dictionary.find(queryArr[i]);
			if (temp != dictionary.end())
				toRet.push_back(temp->second);
		}
	}
	else{
		BlockReader br;
		pair<string, list<Posting> > tempPair;
		vector<string> encoded = fetchFromFile(queryArr);
		for(unsigned int i=0;i<encoded.size();i++){
			tempPair = br.getKeyValue(encoded[i]);
			toRet.push_back(tempPair.second);
		}
	}
	return toRet;
}
void QueryManager::loadDictionary(){
	if(isLoaded){
		return;
	}
	isLoaded = true;
	BlockReader br;
	ifstream reader;
	string line = "";
	pair<string, list<Posting> > tempPair;
	const char* inverted = invertedIndexLocation.c_str();
	reader.open(inverted);
	while(reader.good()){
		getline(reader,line);
		tempPair = br.getKeyValue(line);
		dictionary.insert(tempPair);
	}
	reader.close();
}

QueryManager::QueryManager(string location){
	invertedIndexLocation = location;
	isLoaded = false;
}
bool isNeeded(string line, const vector<string>& queryArr){
	bool good = false;
	for(unsigned int j=0; j<queryArr.size(); j++){
		for(unsigned int i=0;i<queryArr.size();i++){
			if(line[i]!=(queryArr[j])[i]){
				break;
			}
			if(i==(queryArr[j].size()-1) && line[i]=='#'){
				good=true;
			}
		}
	}
	return good;
}
vector<string> QueryManager::fetchFromFile(const vector<string>& queryArr){
	ifstream reader;
	string line;
	char preview;
	const char* inverted = invertedIndexLocation.c_str();
	reader.open(inverted);
	vector<string> toRet;
	while(reader.good()){
		getline(reader,line);
		if(!isNeeded(line, queryArr)){
			continue;
		}
		toRet.push_back(line);
	}
	reader.close();
	return toRet;
}

list<Posting> mergeLists(list<Posting>& l1, list<Posting>& l2){
	list<Posting> final;
	list<Posting>::iterator it1 = l1.begin();
	list<Posting>::iterator it2 = l2.begin();

	while(true)
	{
		if(it1==l1.end() || it2==l2.end()){
			break;
		}

		if(it1->getDocId() < it2->getDocId()){
			it1++;
		}else if(it1->getDocId() > it2->getDocId()){
			it2++;
		}else{
			final.push_back(*it1);
			it1++;
			it2++;
		}
	}
	return final;
}
list<Posting> QueryManager::mergeResults(vector<list<Posting> >& toMerge){
	list<Posting> toRet;
	for(unsigned int i=0; i<toMerge.size();i++){
		if(toMerge.size()==1){
			toRet = toMerge[0];
			return toRet;
		}
		if(i==0){
			toRet = mergeLists(toMerge[i], toMerge[i+1]);
			i++;
		}
		else{
			toRet = mergeLists(toMerge[i], toRet);
		}
	}
	return toRet;	

}


void displayList(list<Posting>& results){
	cout<<"Here are the results:"<<endl;
	for(list<Posting>::iterator it = results.begin(); it != results.end(); it++){
		cout<<"DocID="<<it->getDocId()<<" File="<<it->getFilename()<<endl;
	}
	cout<<endl;
}

list<Posting> QueryManager::performQuery(string query, bool fromDictionary){
	vector<string> queryArr = splitQuery(query, ' ');
	if(fromDictionary){
		loadDictionary();
	}
	vector<list<Posting> > results = fetchPostings(queryArr, fromDictionary);
	for(int i=0; i<results.size();i++){
		cout<< "for:"<< queryArr[i]<<endl;
		displayList(results[i]);
	}
	list<Posting> finalResult = mergeResults(results);
	return finalResult;
}



