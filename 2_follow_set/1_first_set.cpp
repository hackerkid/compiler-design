#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#define m map <string,  vector <string> > 
#define ARROW "→"
#define epsilon ε
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


void fill_terminals()
{
	
	for (m::iterator it = mp.begin(); it != mp.end(); it++) {
		vector <string> row;
		vector <string> expands_to;
		string x;

		x = it->first;
		expands_to = it->second;
		
		int i;
		for (i = 0; i < expands_to.size(); i++) {
			if(!isupper(expands_to[i][0])) {
				row.push_back(expands_to[i]);
			}
		}

		if(row.size() == expands_to.size()) {
			follow_table[x] = row;
		}
	}

	print(follow_table);

}

void create_follow_table()
{
	vector <string> temp;
	bool not_done;

	not_done = false;

	for (m::iterator it = mp.begin(); it != mp.end(); it++) {
		cout << "printing " << it->first << endl;
		char c;
		c = it->first[0];
		string stemp;
		stemp = c;
		if(isupper(c)) {
			follow_table[stemp] = temp;
		}
	}

	fill_terminals();

	
	
	
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
	create_follow_table();
	
}

