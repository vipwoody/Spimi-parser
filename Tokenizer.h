#include <string>
#include <vector>
using namespace std;
class Tokenizer{
	public:
		Tokenizer();
		~Tokenizer();
		void tokenizeLine(string& line, vector<string>& toRet);
};
