#include <iostream>
#include <fstream>
#include <sstream>


enum states { TEXT, SINGLE_QUOTE, SINGLE_SLASH, SINGLE_LINE_COMMENT, MULTI_COMMENT, MULTI_LINE_COMMENT, STAR_FOUND, SINGLE_SINGLE_QUOTE};
using namespace std;

ifstream ifwords("keywords");

//read the file from the file
string read_file(const char * name)
{
	std::ifstream fcin(name);
	std::stringstream buffer;
	
	buffer << fcin.rdbuf();

	return buffer.str();

}

bool check_for_keywords(string word)
{	
	string keyword;
	cout << word << endl;
	while(ifwords >> keyword) {
		if(keyword == word) {
			cout << word << endl;
 			return true;
		}
	}

	return false;
}
//check 

int check_for_tokens(string x)
{
	if(check_for_keywords(x))
		return true;

	return TEXT;
}


void parser(string file)
{	
	int state;
	char c;
	string word;
	state = TEXT;

	for(int i = 0; i < file.length(); i++) {
		c = file[i];
	
		switch(state) {
			case TEXT:

				switch(c) {
					case '/':
						state = SINGLE_SLASH;
						break;

					case '"':
						state = SINGLE_QUOTE;
						break;

					case '\'':
						state = SINGLE_SINGLE_QUOTE;
						break;
					case ' ':
						state = check_for_tokens(word);
						word = "";
					default:
						word = word + c;
						
				}

				break;

			case SINGLE_SLASH:
				switch(c) {
					case '/':
					state = SINGLE_LINE_COMMENT;
					break;

					case '*':
					state = MULTI_LINE_COMMENT;
					break;
				}

				break;

			case SINGLE_LINE_COMMENT:
				switch(c) {
					case '\n':
						state = TEXT;
						word = "";
						break;
				}
				

				break;

			case MULTI_LINE_COMMENT:
				switch(c) {
					case '*':
					state = STAR_FOUND;
				}
				break;

			case STAR_FOUND:
				switch(c) {
					case '/':
						state = TEXT;
						word = "";
						break;
				}
				break;

			case SINGLE_QUOTE:
				switch(c) {
					case '"':
					state = TEXT;
					word = "";
					break;
				}
				break;

			case SINGLE_SINGLE_QUOTE:
				switch(c) {
					case '\'':
						state = TEXT;
						word = "";
						break;
				}

		}		
	}
} 


int main()
{
	string file;

	file = read_file("input");
	parser(file);

}

