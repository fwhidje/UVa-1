#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace::std;
typedef vector<vector<double>> table;

vector<table> read_conversion_table(const string&);
//Een vector die de tabellen bevat
const static vector<table> conversion_table(read_conversion_table("input.txt"));

struct state {
	state() : country(0), value(0), depth(0), parent(NULL){};
	state(unsigned short cou, double val, unsigned short dep, const state* st) : 
		country(cou), value(val), depth(dep), parent(st) {};

	vector<state> generate_children(const unsigned short& tableno);

	unsigned short country;
	double value;
	unsigned short depth;
	const state* parent;
};

vector<state> state::generate_children(const unsigned short& tabelno) {
	vector<state> output;
	for (table::size_type i = 0; i < (conversion_table[tabelno].size()-1); ++i) {
		cerr << conversion_table[tabelno].size()<<" ";
		unsigned short country = (i == this->country ? (++i) : i);
		double value = this->value * conversion_table[tabelno][this->country][i];
		output.push_back(state(country, value, this->depth + 1, this));
	}
	return output;
}

bool succes(const state& st, unsigned short start_country) {
	return (st.country == start_country && st.value > 1.05);
}

vector<table> read_conversion_table(const string& filename) {

	ofstream ouf("output.txt");

	vector<table> outp;
	ifstream inf(filename);
	unsigned short size;
	vector<table>::size_type tablen = 0;
	string temp;
	while (inf >> size) {
		inf.get();
		outp.push_back(table());
		for (table::size_type j = 0; j < size; ++j) {
			getline(inf, temp);
			outp[tablen].push_back(vector<double>());
			istringstream is(temp);
			double i;
			while (is >> i) 
				outp[tablen][j].push_back(i);
		}
		cerr << endl;
		++tablen;
	}
	return outp;
}

int main() {
	ofstream ouf("output.txt");
	state test(1, 1, 0, NULL);
	vector<state> children = test.generate_children(1);
	for (const auto& x : children) {
		ouf << x.country << " " << x.value << endl;
	}


	return 0;
}
