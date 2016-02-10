#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#define m map <string,  vector <string> > 
#define ARROW "→"
#define epsilon "ε"
using namespace std;


void print(m mp)
{
	for ( m::iterator it = mp.begin(); it != mp.end(); it++) {
		cout << it->first << " => ";
		for (int i = 0; i < it->second.size(); i++) {
			cout << it->second[i] <<" ";
		}
		cout << endl;
	}
}

m mp;
m follow_table;

bool terminal(string c)
{

	return !(mp.count(c) != 0);
}

vector <string> create_follow_table(string c)
{

	if(terminal(c)) {
		vector <string> temp;
		temp.push_back(c);
		return temp;
	}

	if(follow_table.count(c)) {
		return follow_table[c];
	}
		
	for (int i = 0; i < mp[c].size(); i++) {
		vector <string> expansions = mp[c];
		bool epsilon_found = true;
		
		for (int j = 0; j < expansions.size() and epsilon_found; j++) {
			vector <string> exp_follows = create_follow_table(expansions[j]);
			epsilon_found = false;

			for (int k = 0; k < exp_follows.size(); k++) {
				if(exp_follows[k] == epsilon) {
					epsilon_found = true;
					if(k == 0) {
						follow_table[c].push_back(epsilon);
					}
				}
				else {
					follow_table[c].push_back(exp_follows[k]);
				}
			}
		}
	}
	

}
void process_input()
{
	
	ifstream fcin("input");
	string line;
	string word;
	bool not_empty;
	bool saw_arrow;
	string non_terminal;
	string expands_to;

	while(getline(fcin, line)) {
		not_empty = false;
		saw_arrow = false;
		istringstream word_processor(line);
			
			while(word_processor >> word) {
				if(word == ARROW) {
					saw_arrow = true;
					continue;
				}
				
				if(!saw_arrow) {
					non_terminal = word;
				}
				else {
					mp[non_terminal].push_back(word);
				}
				
				not_empty = true;
			}

	}

}

int main()
{
	process_input();

	print(mp);

	create_follow_table();
	
}

