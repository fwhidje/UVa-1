/*
Run the main_*_program and supply a (.txt) file.
Output is an "output.txt"-file.
*/
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>

using namespace::std;
typedef vector<int> one_box;
typedef vector<one_box> all_boxes;

/*
neemt een vector<vector<int>> en doet hiermee:
	1) voegt een nummer toe aan het einde (0,1,...)
	2) sorteert de vector */
void prepare_all_boxes(all_boxes& boxes) {
	for (all_boxes::size_type i = 0; i < boxes.size(); ++i)
		boxes[i].push_back(i+1);
	sort(boxes.begin(), boxes.end(), [](one_box a, one_box b) {return accumulate(a.begin(), a.end()-1, 0) < accumulate(b.begin(), b.end()-1, 0); });
	for (auto& x : boxes)
		sort(x.begin(), x.end()-1);
}

bool fits_in(one_box a, one_box b) {
	for (one_box::const_iterator i = a.begin(), j = b.begin(); i != a.end()-1; ++i, ++j)
		if (*i > *j)
			return false;
	return true;
}

vector<int> search_longest(all_boxes& boxes) {
	prepare_all_boxes(boxes);
	vector<vector<int>> found_series;
	one_box current;
	for (all_boxes::size_type i = 0; i < boxes.size(); ++i) {
		current = boxes[i];
		found_series.push_back({ current.back() });
		for (all_boxes::size_type j = i+1; j < boxes.size(); ++j) {
			if (fits_in(current, boxes[j])) {
				current = boxes[j];
				found_series[i].push_back(current.back());
			}
		}
	}
	sort(found_series.begin(), found_series.end(), [](vector<int> a, vector<int> b) {return a.size() > b.size(); });
	return found_series.front();
}

vector<all_boxes> read_input(const string& filename) {
	vector<all_boxes> allboxes;
	ifstream fs(filename);
	string hold;

	while (getline(fs, hold)) {
		all_boxes boxes;

		istringstream ss1(hold);
		int a, b;
		ss1 >> a >> b;
		for (int i = 0; i < a; ++i) {
			one_box box;

			getline(fs, hold);
			istringstream ss2(hold);
			while (ss2 >> b) {
				box.push_back(b);
			}
			boxes.push_back(box);
		}
		allboxes.push_back(boxes);
	}
	return allboxes;
}

string write_output(vector<int> vec) {
	ostringstream os;
	os << vec.size() << endl;
	for (const auto& x : vec)
		os << x << " ";
	os << endl;
	return os.str();
}

void main_boxes_program(const string& filename) {
	vector<all_boxes> allboxes = read_input(filename);
	ofstream of("output.txt");
	for (auto boxes : allboxes)
		of << write_output(search_longest(boxes));
}