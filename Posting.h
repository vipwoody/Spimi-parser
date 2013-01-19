#ifndef postingclass
#define postingclass
#include <string>
using namespace std;
class Posting{
	private: 
		long docId;
		string filename;
		int frequency;
	public:
		Posting();
		Posting(string fn);
		Posting(Posting* posting);
		~Posting();
		long getDocId();
		void setDocId(long did);
		string getFilename();
		void setFilename(string filename) ;
		int getFrequency(); 
		void setFrequency(int fr); 
		void addFrequency();
		string getFullText();
		string toBlock();
		bool Equals(const Posting& posting) const;
		string toString();
	        bool operator==(const Posting &other) const;
};

#endif
