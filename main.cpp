#include "SpimiParser.h"
#include "SpimiMerger.h"
#include "QueryManager.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

void displayResults(list<Posting>& results){
	cout<<"Here are the results of your search:"<<endl;
	for(list<Posting>::iterator it = results.begin(); it != results.end(); it++){
		cout<<"DocID="<<it->getDocId()<<" File="<<it->getFilename()<<endl;
	}
	cout<<endl;
}

void displayMenu(int i){
	if(i==1){
		cout<< "Please provide a number for the amount of space the Spimi Reader will be allowed to use(ex:10,000)"<<endl;
	}
	else{
		cout << "Welcome to Spimi parser, what would you like to do?" << endl;
		cout << "1. Index files and merge them to a final inverted index"<< endl;
		cout << "2. Search"<< endl;
		cout << "3. Exit"<<endl;
	}

}
void applySpimi(long space){
	vector<string> filenames;
	string invertedIndexFile;

	filenames.push_back("Reuters/reut2-000.sgm");
	filenames.push_back("Reuters/reut2-001.sgm");
	filenames.push_back("Reuters/reut2-002.sgm");
	filenames.push_back("Reuters/reut2-003.sgm");
	filenames.push_back("Reuters/reut2-004.sgm");
	filenames.push_back("Reuters/reut2-005.sgm");
	filenames.push_back("Reuters/reut2-006.sgm");
	filenames.push_back("Reuters/reut2-007.sgm");
	filenames.push_back("Reuters/reut2-008.sgm");
	filenames.push_back("Reuters/reut2-009.sgm");
	filenames.push_back("Reuters/reut2-010.sgm");
	filenames.push_back("Reuters/reut2-011.sgm");
	filenames.push_back("Reuters/reut2-012.sgm");
	filenames.push_back("Reuters/reut2-013.sgm");
	filenames.push_back("Reuters/reut2-014.sgm");
	filenames.push_back("Reuters/reut2-015.sgm");
	filenames.push_back("Reuters/reut2-016.sgm");
	filenames.push_back("Reuters/reut2-017.sgm");
	filenames.push_back("Reuters/reut2-018.sgm");
	filenames.push_back("Reuters/reut2-019.sgm");
	filenames.push_back("Reuters/reut2-020.sgm");
	filenames.push_back("Reuters/reut2-021.sgm");

	SpimiParser* parser = new SpimiParser(filenames, space);
	filenames = parser->parseFiles();
	delete parser;
	

	SpimiMerger* merger = new SpimiMerger(filenames);
	filenames = merger->mergeFiles();
	invertedIndexFile = merger->finalMerge();
	delete merger;
}
void doQuery(){
	string invertedIndex = "final_index.txt";
	QueryManager qm(invertedIndex);
	string query;
	char line[100];
	list<Posting> searchResults;
	while(true){
		cout << "Please enter a query (or 0 to go back to main menu)" << endl;
		cin.getline(line, 100);
		stringstream converter;
		converter << line;
		query = converter.str();
		converter.flush();
		if(query=="0"){
			break;
		}
		searchResults = qm.performQuery(query, true);
		displayResults(searchResults);
	}
}
int main(){
	int terminate;
	int menuInput;
	long space;
	bool done=false;
	while(!done){
		displayMenu(0);
		cin >> menuInput;
		if(menuInput==1){
			displayMenu(1);
			cin >> space;
			applySpimi(space);
		}
		else if(menuInput==2){
			doQuery();
		}
		else if(menuInput==3){
			done = true;
		}	
	}


	cout << "Hope you enjoyed this Spimi Parser";
	cin >> terminate;
	return 0;
}	
