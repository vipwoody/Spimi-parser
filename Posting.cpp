#include "Posting.h"
#include <sstream>
#include <string>
using namespace std;
static long uniqueDocId=0;
Posting::Posting(){
		this->docId = uniqueDocId++;
		this->filename = "";
		this->frequency = 1;
}
Posting::Posting(string fn){
	docId = uniqueDocId++;
	filename = fn;
	frequency = 1;
}
Posting::Posting(Posting* posting){
	this->docId = posting->docId;
	this->filename = posting->filename;
	this->frequency = posting->frequency;
}
Posting::~Posting(){

}
	
long Posting::getDocId() {
	return docId;
}

void Posting::setDocId(long did) {
	docId = did;
}

string Posting::getFilename() {
	return this->filename;
}

void Posting::setFilename(string fn) {
	this->filename = fn;
}

int Posting::getFrequency() {
	return frequency;
}
void Posting::setFrequency(int fr) {
	frequency = fr;
}
void Posting::addFrequency() {
	this->frequency++;
}
string Posting::getFullText(){
	return "FULL TEXT OF DOCUMENT "+ this->docId;
}
	
string Posting::toBlock(){
	string delimiter="&";
	stringstream convert;
	convert << this->docId << delimiter << this->filename << delimiter << this->frequency;
	string toRet=convert.str();
	return toRet;
}
bool Posting::operator==(const Posting &other) const
{
	return Equals(other);
}
bool Posting::Equals(const Posting& posting) const{
	return (this->docId == posting.docId);
}
string Posting::toString(){
	stringstream convert;
	convert << "Doc Id: " << docId << " | File Name:  "<< filename << " | Frequency = "<< frequency;
	string toRet = convert.str();
	return toRet;
}
