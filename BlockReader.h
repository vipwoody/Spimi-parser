#include <vector>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "Posting.h"
using namespace std;
class BlockReader{
	public:
		BlockReader();
		~BlockReader();
		pair<string,list<Posting> > getKeyValue(string line);
};
