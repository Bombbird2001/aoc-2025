#include <iostream>
#include <string>

using namespace std;

int main() {
	vector<string> beamMap;

	int lineIndex = 0;
	for (string line; getline(cin, line);) {
		if (lineIndex % 2 == 0) {
			beamMap.push_back(line);
		}

		lineIndex++;
	}

	int splits = 0;
	for (int r = 0; r < beamMap.size(); r++) {
		for (int i = 0; i < beamMap[r].length(); i++) {
			char c = beamMap[r][i];
			if (c == 'S') beamMap[r][i] = '|';
			else if (c == '^' && r > 0 && beamMap[r - 1][i] == '|') {
				if (i > 0) beamMap[r][i - 1] = '|';
				if (i < beamMap[r].length() - 1) beamMap[r][i + 1] = '|';
				splits++;
			} else if (c == '.' && r > 0 && beamMap[r - 1][i] == '|') {
				beamMap[r][i] = '|';
			}
		}
	}

	cout << splits << endl;

	return 0;
}
