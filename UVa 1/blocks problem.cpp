#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace::std;

vector<vector<int>> generate_initial(int i) {
	vector<vector<int>> ret(i);
	for (int j = 0; j < i; j++) {
		ret[j].push_back(j);
	}
	return ret;
}

void clear_above(int a, vector<int>& stck, vector<vector<int>>& blocks) {
	while (stck.back() != a) {
		blocks[stck.back()].push_back(stck.back());
		stck.pop_back();
	}
}

//Controleert niet of het getal niet is gevonden!
vector<int>* find_block_tower(int a, vector<vector<int>>& vec) {
	for (auto& x: vec) 
		if (find(x.begin(), x.end(), a) != x.end())
			return &x;
}

//plaatst b op a!
void move_onto(int b, int a, vector<vector<int>>& vec) {
	vector<int> *has_a = find_block_tower(a,vec), 
		*has_b = find_block_tower(b,vec);	
	if (has_a == has_b)
		return;
	clear_above(a, *has_a, vec);
	clear_above(b, *has_b, vec);
	has_a->push_back(b);
	has_b->pop_back();
}

void move_over(int b, int a, vector<vector<int>>& vec) {
	vector<int> *has_a = find_block_tower(a, vec),
		*has_b = find_block_tower(b, vec);
	if (has_a == has_b)
		return;
	clear_above(b, *has_b, vec);
	has_a->push_back(b);
	has_b->pop_back();
}

void pile_onto(int b, int a, vector<vector<int>>& vec) {
	vector<int> *has_a = find_block_tower(a, vec),
		*has_b = find_block_tower(b, vec);
	if (has_a == has_b)
		return;
	clear_above(a, *has_a, vec);
	vector<int>::iterator b_point = find(has_b->begin(), has_b->end(), b);
	copy(b_point, has_b->end(), back_inserter(*has_a));
	has_b->erase(b_point, has_b->end());
}

void pile_over(int b, int a, vector<vector<int>>& vec) {
	vector<int> *has_a = find_block_tower(a, vec),
		*has_b = find_block_tower(b, vec);
	if (has_a == has_b)
		return;
	vector<int>::iterator b_point = find(has_b->begin(), has_b->end(), b);
	copy(b_point, has_b->end(), back_inserter(*has_a));
	has_b->erase(b_point, has_b->end());
}

//print naar output file
void print(vector<vector<int>> vec) {
	ofstream outp("output.txt");
	for (vector<vector<int>>::size_type i = 0; i < vec.size(); ++i) {
		outp << i << ":";
		for (const auto& y : vec[i])
			outp << " "<< y;
		outp << endl;
	}
}

void call_func(string s, int a,int b, vector<vector<int>>& vec) {
	map<string, void(*) (int, int, vector<vector<int>>&)> funcmap =
		{ {"moveonto", move_onto}, {"moveover", move_over},{"pileonto", pile_onto},{"pileover", pile_over} };
	funcmap[s](a, b, vec);
}

void program_main(const char* filename) {
	ifstream file(filename);
	if (!file) return;

	string s, s1, s2;
	int a, b;
	file >> a;
	vector<vector<int>> blocks = generate_initial(a);
	while (std::getline(file, s)) {
		istringstream ss(s);
		if (ss >> s1 >> a >> s2 >> b) 
			call_func((s1+s2), a, b, blocks);
		else if (s1 == "quit")
			print(blocks);
	}
}

/*int main() {
	program_main("input.txt");
	return 0;
}*/

