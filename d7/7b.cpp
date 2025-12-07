#include <iostream>
#include <string>
#include <algorithm>
#include <stdint.h>

using namespace std;

int main() {
	vector<vector<int64_t>> beamMap;

	int lineIndex = 0;
	int startIndex = -1;
	for (string line; getline(cin, line);) {
		if (lineIndex % 2 == 0) {
			if (lineIndex == 0) startIndex = line.find('S');
			vector<int64_t> row;
			for (int j = 0; j < line.length(); j++) {
				if (line[j] == '^') row.push_back(-1);
				else row.push_back(0);
			}
			beamMap.push_back(row);
		}

		lineIndex++;
	}

	// Initialise number in last row
	for (int c = 0; c < beamMap.back().size(); c++) {
		if (beamMap.back()[c] == 0) beamMap.back()[c] = 1;
	}

	for (int r = beamMap.size() - 1; r > 0; r--) {
		for (int c = 0; c < beamMap[r].size(); c++) {
			int64_t ch = beamMap[r][c];
			if (ch == -1 && beamMap[r - 1][c] != -1) {
				int64_t leftNo = 0;
				if (c > 0) leftNo = beamMap[r][c - 1];
				int64_t rightNo = 0;
				if (c < beamMap[r].size() - 1) rightNo = beamMap[r][c + 1];
				beamMap[r - 1][c] = leftNo + rightNo;
			} else if (beamMap[r - 1][c] != -1) {
				beamMap[r - 1][c] = ch;
			}
		}
	}

	cout << beamMap[0][startIndex] << endl;

	return 0;
}
