#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#define m map <string,  vector <string> > 
#define ARROW "→"
#define EPSILON "ε"
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

	return (mp.count(c) == 0);
}

/*
void create_follow_table(string c)
{	

	cout << "c " << c << endl;

	if(terminal(c)) {
		vector <string> temp;
		//temp.push_back(c);
		//return temp;
	}

	if(follow_table.count(c)) {
		//return follow_table[c];
	}
	
	//iterate through all the exapnsions

	/*
	for (int i = 0; i < mp[c].size(); i++) {
		string expansions = mp[c][i];
		bool EPSILON_found = true;
		
		cout << "expansions " << expansions << endl; 

		//itereate through all the chars in an expansion

		/*
		for (int j = 0; j < expansions.length() and EPSILON_found; j++) {
			string c_to_st;
			char c;
			c = expansions[j];
			c_to_st = c;
			
			vector <string> exp_follows = create_follow_table(c_to_st);
			EPSILON_found = false;

			for (int k = 0; k < exp_follows.size(); k++) {
				if(exp_follows[k] == EPSILON) {
					EPSILON_found = true;
					if(k == 0) {
						follow_table[c].push_back(EPSILON);
					}
				}
				else {
					follow_table[c].push_back(exp_follows[k]);
				}
			}
		}
	}

		

}
*/
vector <string>  create(string c)
{
	vector <string> temp;
	cout << " the input is " << c << endl;
	if(terminal(c)) {
		cout << "hell yeah" << c << endl;
		follow_table[c].push_back(c);
		temp.push_back(c);
		return temp;
	}

	cout << "see the productions" << endl;

	for (int i = 0; i < mp[c].size(); i++) {
		if(mp[c][i] == EPSILON) {
			follow_table[c].push_back(EPSILON);
			temp.push_back(EPSILON);
			return temp;
		}
		else {
			if(terminal(mp[c][i])) {

				follow_table[c].push_back(mp[c][i]);
				temp.push_back(mp[c][i]);
				return temp;
			}
			else {
				cout << mp[c][i] << 
				bool epsilon_found = false;
				
				for (int k = 0; k < mp[c][i].length() and !epsilon_found; k++) { 
					char single_element;

					single_element = mp[c][i][k];
					string letter(1,single_element );
					vector <string> result = create(letter);

					for (int l = 0; l < result.size(); l++) {
						follow_table[c].push_back(result[l]);
						temp.push_back(result[l]);
					}

				}
			}
		}

	}

	return temp;

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

	create("E");
	
}

