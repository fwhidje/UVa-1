#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

using namespace::std;

//calculates the cost of moving all the bottles of a 'color' (0,1,2) to each of the bins.
//Returns a vector of size 3
vector<unsigned int> find_cost(int col, const vector<unsigned int>& bins) {
	vector<unsigned int> ret(3, bins[col] + bins[col + 3] + bins[col + 6]);
	for (vector<unsigned int>::size_type i = 0; i < 3; ++i)
		ret[i] -= bins[col + i*3];
	return ret;
}

//Returnt vector<int> grootte 9 met daarin [B(1,2,3)-G(1,2,3)-C(1,2,3)] 
vector<unsigned int> find_all_costs(const vector<unsigned int>& bins) {
	vector<unsigned int> ret;
	for (int i = 0; i < 3; ++i) {
		vector<unsigned int> temp = find_cost(i, bins);
		copy(temp.begin(), temp.end(), back_inserter(ret));
	}
	return ret;
}

//Returnt vector<vector<int>> met daarin [{x,y,z,cost},...]
//formaat x,y,z: welke kleur in die bin gaat. (i.e. 0,1,2)
vector<vector<unsigned int>> find_cheapest(const vector<unsigned int>& bins) {
	vector<vector<unsigned int>> ret;
	unsigned int total = -1;
	for(unsigned int i = 0; i < 3; ++i)
		for(unsigned int j = 0; j < 3; ++j)
			for (unsigned int k = 0; k < 3; ++k) {
				if (i == j || j == k || k == i)
					continue;
				unsigned int sum = bins[i] + bins[3 + j] + bins[6 + k];
				if (sum > total)
					continue;
				if (sum == total)
					ret.push_back({ i,j,k,sum });
				if (sum < total) {
					ret.clear();
					ret.push_back({ i,j,k,sum });
					total = sum;
				}
			}
	return ret;
}

vector<unsigned int> sort_alpha(vector<vector<unsigned int>> bins) {
	sort(bins.begin(), bins.end(), [](vector<unsigned int> a, vector<unsigned int> b) {return a[2] < b[2]; });
	stable_sort(bins.begin(), bins.end(), [](vector<unsigned int> a, vector<unsigned int> b) {return a[0] < b[0]; });
	return bins[0];
}

pair<string,int> find_best_ordening(const vector<unsigned int>& bins) {
	vector<unsigned int> ret = sort_alpha(find_cheapest(find_all_costs(bins)));
	string code(3, ' ');
	char carr[] = { 'B', 'G', 'C' };
	for (int i = 0; i < 3; ++i)
		code[ret[i]] = carr[i];
	return{ code, ret[3] };
}

void main_program(const string& filename) {
	vector<unsigned int> work;
	pair<string, int> out;

	ifstream file(filename);
	ofstream outp("output.txt");
	string s;
	while (std::getline(file, s)) {
		work.clear();
		istringstream ss(s);
		int a;
		while (ss >> a)
			work.push_back(a);
		out = find_best_ordening(work);
		outp << out.first << " " << out.second << endl;
	}
}
