#include <iostream>
#include <string>

using namespace std;

int main() {
	vector<int> spaces;

	int shapeSpaceCount = 0;
	int fitCount = 0;
	for (string line; getline(cin, line);) {
		if (line.empty()) spaces.push_back(shapeSpaceCount);
		else if (line[line.length() - 1] == ':') {
			shapeSpaceCount = 0;
		} else if (line[0] == '.' || line[0] == '#') {
			for (char c: line) {
				if (c == '#') shapeSpaceCount++;
			}
		} else {
			int parsingPhase = 0;
			int dim1 = 0;
			int dim2 = 0;

			int spacesNeeded = 0;
			int spaceCount = 0;
			int spaceParseIndex = -1;
			for (int i = 0; i < line.length(); i++) {
				char c = line[i];
				if (parsingPhase == 0) {
					if (c == 'x') parsingPhase = 1;
					else {
						dim1 *= 10;
						dim1 += (c - '0');
					}
				} else if (parsingPhase == 1) {
					if (c == ':') parsingPhase = 2;
					else {
						dim2 *= 10;
						dim2 += (c - '0');
					}
				} else if (parsingPhase == 2) {
					if (c == ' ') {
						spacesNeeded += (spaceCount * spaces[spaceParseIndex]);
						spaceParseIndex++;
						spaceCount = 0;
					} else {
						spaceCount *= 10;
						spaceCount += (c - '0');
						if (i == line.length() - 1) {
							spacesNeeded += (spaceCount * spaces[spaceParseIndex]);
						}
					}
				}
			}

			if (spacesNeeded <= dim1 * dim2) fitCount++;
		}
	}

	cout << fitCount << endl;

	return 0;
}
