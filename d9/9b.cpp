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
			if (deltaX * deltaY <= maxArea) continue;

			// Check all 4 sides are inside bounding region
			// We are given the coordinates in clockwise order
			// Check using following rules:
			// Only need to be checked if x/y range crosses the changing dimension
			// If x coordinate is greater and y coordinate is same, check smallest y coordinate is >= y coordinate
			// If x coordinate is smaller and y coordinate is same, check biggest y coordinate is <= y coordinate
			// If y coordinate is greater and x coordinate is same, check biggest x coordinate is <= x coordinate
			// If y coordinate is smaller and x coordinate is same, check smallest x coordinate is >= x coordinate
			int64_t smallestX = min(coords[i].x, coords[j].x);
			int64_t biggestX = max(coords[i].x, coords[j].x);
			int64_t smallestY = min(coords[i].y, coords[j].y);
			int64_t biggestY = max(coords[i].y, coords[j].y);
			bool violated = false;
			for (int k = 0; k < coords.size(); k++) {
				int nextIndex = (k + 1) % coords.size();
				if (coords[k].x < coords[nextIndex].x && coords[k].y == coords[nextIndex].y) {
					if (smallestY < coords[k].y && biggestY >= coords[k].y && biggestX > coords[k].x && smallestX < coords[nextIndex].x) {
						violated = true;
						break;
					}
				} else if (coords[k].x > coords[nextIndex].x && coords[k].y == coords[nextIndex].y) {
					if (biggestY > coords[k].y && smallestY <= coords[k].y && biggestX > coords[nextIndex].x && smallestX < coords[k].x) {
						violated = true;
						break;
					}
				} else if (coords[k].y < coords[nextIndex].y && coords[k].x == coords[nextIndex].x) {
					if (biggestX > coords[k].x && smallestX <= coords[k].x && biggestY > coords[k].y && smallestY < coords[nextIndex].y) {
						violated = true;
						break;
					}
				} else if (coords[k].y > coords[nextIndex].y && coords[k].x == coords[nextIndex].x) {
					if (smallestX < coords[k].x && biggestX >= coords[k].x && biggestY > coords[nextIndex].y && smallestY < coords[k].y) {
						violated = true;
						break;
					}
				} else {
					cout << "Invalid state reached: " << coords[k].x << "," << coords[k].y << "-->" << coords[nextIndex].x << "," << coords[nextIndex].y << endl;
				}
			}
			if (violated) continue;

			maxArea = deltaX * deltaY;
		}
	}

	cout << maxArea << endl;

	return 0;
}
