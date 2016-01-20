#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


enum states { NEW_WORD, NUMBER, IDENTIFIER, SINGLE_QUOTE, SINGLE_SLASH, SINGLE_LINE_COMMENT, MULTI_COMMENT, MULTI_LINE_COMMENT, STAR_FOUND, SINGLE_SINGLE_QUOTE, DATA_TYPE, KEY_WORD};
using namespace std;

typedef struct simple_table
{
	string identifer;
	string data_type;
	string scope;
} simple_table;

vector <string> number_arr;
vector <string> keyword_arr;
vector <string> identifer_arr;
vector <simple_table> simple_table_arr;


bool region_opening(char c)
{
	if(c == '{' or c == '(') {
		return true;
	}

	return false;

}
bool region_closing(char c)
{
	if(c == '}' or c == ')') {
		return true;
	}

	return false;

}
int is_data_type(string x)
{

	string types[] = {"byte", "short", "int", "long", "float", "double", "boolean", "char"};
	
	for (int i = 0; i < types[i].size(); i++) {
		if(types[i] == x) {
			return 1;
		}
	}

	return false;
}
string braceid_to_string( int x)
{
	string res;
	int temp;
	char c;
	temp = x;

	res = "";
	if(x == 0) {
		res = "0";
	}
	while(x) {
		c = x % 10 + '0';
		res = c + res; 
		x = x / 10;
	}
	//string ans = id + " { inside region " + res + " }";
	return res;
}
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
	ifstream ifwords("keywords");
	while(ifwords >> keyword) {
		if(keyword == word) {
 			return true;
		}
	}

	return false;
}

int check_for_tokens(string x)
{
	if(check_for_keywords(x)) {
		return 1;
	}

	return 0;
}


void parser(string file)
{	
	int state;
	char c;
	int brace_count;
	string word;
	string previous_word;

	brace_count = 0;

	state = NEW_WORD;

	for(int i = 0; i < file.length(); i++) {
		c = file[i];
	
		switch(state) {
			// new word is just read

			case NEW_WORD:
			// hell yaeh identifer or keyword
				if(isalpha(c) or c == '_') {
					state = IDENTIFIER;
					word = word + c;
					break;

				}
			//its a digit

				if(isdigit(c)) {
					state = NUMBER;
					word = word + c;
					break;
				}

				if(region_opening(c)) {
					brace_count++;
				}
				if(region_closing(c)) {
					brace_count--;
				}

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
					case '\n':
					case ';':
					case '(':
					case ')':
					case '[':
					case ']':
					case '*':
					case '+':
					case '=':
					case '-':
					case '\t':
					case '{':
					case '}':
					case '<' :
						previous_word = word;
						word = "";
						state = NEW_WORD;
						break;

						
				}

				break;

			case IDENTIFIER:

				if(region_opening(c)) {
					brace_count++;
				}
				if(region_closing(c)) {
					brace_count--;
				}

				switch(c) {
					case ' ':
					case '\n':
					case ';':
					case '(':
					case ')':
					case '[':
					case ']':
					case '*':
					case '+':
					case '=':
					case '-':
					case '\t':
					case '{':
					case '}':
					case '<' :
						if(check_for_tokens(word)) {
							keyword_arr.push_back(word);
						}
						else {
							if(is_data_type(previous_word)) {
								//string id = braceid_to_string(word, brace_count);
								simple_table temp;
								temp.data_type = previous_word;
								temp.scope = braceid_to_string(brace_count);
								temp.identifer = word;

								simple_table_arr.push_back(temp);

								//cout << id << " data " << previous_word << endl;
							}
							identifer_arr.push_back(word);
						}

						previous_word = word;
						word = "";
						state = NEW_WORD;
						break;

					default:
						word = word + c;
						state = IDENTIFIER;
						break;
				}
				break;

			case NUMBER:
				if(isdigit(c)) {
					word = word + c;
					break;
				}
				number_arr.push_back(word);
				previous_word = word;
				word = "";
				state = NEW_WORD;
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
						state = NEW_WORD;
						previous_word = word;
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
						state = NEW_WORD;
						previous_word = word;
						word = "";
						break;
				}
				break;

			case SINGLE_QUOTE:
				switch(c) {
					case '"':
					state = NEW_WORD;
					previous_word = word;
					word = "";
					break;
				}
				break;

			case SINGLE_SINGLE_QUOTE:
				switch(c) {
					case '\'':
						state = NEW_WORD;
						previous_word = word;
						word = "";
						break;
				}

		}		
	}
} 

void print_simple_table()
{
	cout << "SIMPLE TABLE\n";
	cout << "-----------\n\n";

	for (int i = 0; i < simple_table_arr.size(); i++) {
		cout << simple_table_arr[i].identifer << " " << simple_table_arr[i].data_type << " " << simple_table_arr[i].scope << endl;
	}

	cout << "\n\n";
}
	
	

void print_identifiers()
{	
	cout << "IDENTIFIERS\n";
	cout << "-----------\n\n";

	for (int i = 0; i < identifer_arr.size(); i++) {
		cout << identifer_arr[i] << endl;
	}
	cout << "\n";
}

void print_keywords()
{	
	cout << "KEYWORDS\n";
	cout << "-----------\n\n";

	for (int i = 0; i < keyword_arr.size(); i++) {
		cout << keyword_arr[i] << endl;
	}
	cout << "\n";

}

void print_numbers()
{	
	cout << "NUMBERS\n";
	cout << "-----------\n\n";

	for (int i = 0; i < number_arr.size(); i++) {
		cout << number_arr[i] << endl;
	}
	cout << "\n";

}


int main()
{
	string file;

	file = read_file("input");

	
	parser(file);

	print_identifiers();
	print_keywords();
	print_numbers();
	print_simple_table();

}

