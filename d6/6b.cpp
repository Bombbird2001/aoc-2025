#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

int main() {
	vector<string> data;
	vector<char> ops;

	for (string line; getline(cin, line);) {
		data.push_back(line);	
	}

	int maxLength = data[0].length();
	string lastLine = data.back();
	data.pop_back();
	for (int i = 0; i < maxLength; i++) {
		if (lastLine[i] == ' ') continue;
		ops.push_back(lastLine[i]);
	}
	int rows = data.size();

	int64_t total = 0;

	int opCounter = ops.size() - 1;
	int64_t opAccum = 0;
	if (ops[opCounter] == '*') opAccum = 1;
	for (int col = maxLength - 1; col >= 0; col--) {
		int64_t no = 0;
		int64_t pv = 1;
		bool foundNonBlank = false;
		for (int row = rows - 1; row >= 0; row--) {
			char c = data[row][col];
			if (c == ' ') continue;
			foundNonBlank = true;
			no += (c - '0') * pv;
			pv *= 10;
		}

		// If all columns are blank, denotes separator and end of current op
		if (!foundNonBlank) {
			opCounter--;
			total += opAccum;
			opAccum = 0;
			if (ops[opCounter] == '*') opAccum = 1;
		} else {
			if (ops[opCounter] == '*') opAccum *= no;
			else opAccum += no;
		}
	}

	total += opAccum;

	cout << total << endl;
	
	return 0;
}
