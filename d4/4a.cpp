#include <iostream>
#include <string>
#include <vector>

using namespace std;

int isOccupied(vector<string> *map, int row, int column) {
	if (row < 0 || row >= (*map).size() || column < 0 || column >= (*map)[row].length()) return 0;

	if ((*map)[row][column] == '@') return 1;

	return 0;
}

int main() {
	vector<string> map;

	for (string line; getline(cin, line);) {
		map.push_back(line);
	}

	int accessible = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].length(); j++) {
			if (map[i][j] != '@') continue;

			int adjacentCount = 0;
			for (int i1 = -1; i1 < 2; i1++) {
				for (int j1 = -1; j1 < 2; j1++) {
					adjacentCount += isOccupied(&map, i + i1, j + j1);
				}
			}

			// <= 4 since it counts itself
			if (adjacentCount <= 4) {
				accessible++;
			}
		}
	}

	cout << accessible << endl;

	return 0;
}
