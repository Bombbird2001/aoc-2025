#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

int main() {
	vector<vector<int64_t>> nos;
	vector<char> ops;

	for (string line; getline(cin, line);) {
		char firstChar = line[0];
		if (firstChar == '*' || firstChar == '+') {
			for (int i = line.length() - 1; i >= 0; i--) {
				char c = line[i];
				if (c == ' ') continue;
				ops.push_back(c);
			}
			break;
		}
		nos.push_back(vector<int64_t>());
		bool prevEmpty = true;
		int64_t no = 0;
		int64_t pv = 1;
		for (int i = line.length() - 1; i >= 0; i--) {
			char c = line[i];
			if (c == ' ' && !prevEmpty) {
				nos.back().push_back(no);
				no = 0;
				pv = 1;
				prevEmpty = true;
			} else if (c != ' ') {
				no += pv * (c - '0');
				pv *= 10;
				prevEmpty = false;
			} else {
				prevEmpty = true;
			}

			if (i == 0 && c != ' ') nos.back().push_back(no);
		}
	}

	int64_t total = 0;

	for (int i = 0; i < ops.size(); i++) {
		int64_t accum = nos[0][i];
		bool isMul = ops[i] == '*';
		for (int j = 1; j < nos.size(); j++) {
			if (isMul) accum *= nos[j][i];
			else accum += nos[j][i];
		}

		total += accum;
	}

	cout << total << endl;

	return 0;
}
