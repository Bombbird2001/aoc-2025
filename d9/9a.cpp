#include <iostream>
#include <string>
#include <stdint.h>
#include <algorithm>

using namespace std;

struct coord {
	int64_t x;
	int64_t y;
};

int main() {
	vector<coord> coords;

	for (string line; getline(cin, line);) {
		int no = 0;
		int pv = 1;
		coord point;
		for (int i = line.length() - 1; i >= 0; i--) {
			char c = line[i];
			if (c == ',') {
				point.y = no;
				no = 0;
				pv = 1;
			} else {
				no += (c - '0') * pv;
				pv *= 10;
			}
			if (i == 0) point.x = no;
		}
		coords.push_back(point);
	}

	// for (auto pt: coords) {
	// 	cout << pt.x << "," << pt.y << endl;
	// }

	int64_t maxArea = 0;
	for (int i = 0; i < coords.size(); i++) {
		for (int j = i + 1; j < coords.size(); j++) {
			int64_t deltaX = abs(coords[i].x - coords[j].x) + 1;
			int64_t deltaY = abs(coords[i].y - coords[j].y) + 1;
			maxArea = max(maxArea, deltaX * deltaY);
		}
	}

	cout << maxArea << endl;

	return 0;
}
