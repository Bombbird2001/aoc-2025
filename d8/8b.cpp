#include <iostream>
#include <string>
#include <stdint.h>
#include <algorithm>

#define JUNCTIONS 1000

using namespace std;

struct pos {
	int x;
	int y;
	int z;
};

struct distPair {
	int index1;
	int x1;
	int y1;
	int z1;
	int index2;
	int x2;
	int y2;
	int z2;
	int64_t dist;
};

bool comp(distPair p1, distPair p2) {
	return p1.dist < p2.dist;
}

int main() {
	pos positions[JUNCTIONS];

	int indexTracker = 0;
	for (string line; getline(cin, line);) {
		int posIndex = 2;
		int no = 0;
		int pv = 1;
		pos position;
		for (int i = line.length() - 1; i >= 0; i--) {
			char c = line[i];
			if (c == ',') {
				if (posIndex == 2) {
					position.z = no;
				} else if (posIndex == 1) {
					position.y = no;
				}
				no = 0;
				pv = 1;
				posIndex--;
			} else {
				no += pv * (c - '0');
				pv *= 10;
			}

			if (i == 0) position.x = no;
		}
		positions[indexTracker] = position;
		indexTracker++;
	}

	// for (auto pos: positions) {
	//	cout << pos.x << "," << pos.y << "," << pos.z << endl;
	// }

	vector<distPair> allPairs;
	for (int i = 0; i < JUNCTIONS; i++) {
		for (int j = i + 1; j < JUNCTIONS; j++) {
			int64_t deltaX = positions[i].x - positions[j].x;
			int64_t deltaY = positions[i].y - positions[j].y;
			int64_t deltaZ = positions[i].z - positions[j].z;
			int64_t distSquared = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;

			distPair newPair = { i, positions[i].x, positions[i].y, positions[i].z, j, positions[j].x, positions[j].y, positions[j].z, distSquared };
			allPairs.push_back(newPair);
		}
	}

	sort(allPairs.begin(), allPairs.end(), comp);
	
	// for (auto sth: closestPairs) {
	//  	cout << sth.index1 << ": " << sth.x1 << " " << sth.y1 << " " << sth.z1 << ", " << sth.index2 << ": " << sth.x2 << " " << sth.y2 << " " << sth.z2 << " " << sth.dist << endl;
	// }

	// Very unoptimal solution for identifying sets
	int groups[JUNCTIONS];
	fill_n(groups, JUNCTIONS, -1);
	int nextGroup = 0;
	for (auto conn: allPairs) {
		if (groups[conn.index1] == -1 && groups[conn.index2] == -1) {
			groups[conn.index1] = nextGroup;
			groups[conn.index2] = nextGroup;
			nextGroup++;
		} else if (groups[conn.index1] == -1) {
			groups[conn.index1] = groups[conn.index2];
		} else if (groups[conn.index2] == -1) {
			groups[conn.index2] = groups[conn.index1];
		} else if (groups[conn.index1] != groups[conn.index2]) {
			// Just use index1 as the parent lol
			// Very not proud of this code tbh
			int toCheck = groups[conn.index2];
			for (int i = 0; i < JUNCTIONS; i++) {
				if (groups[i] == toCheck) groups[i] = groups[conn.index1];
			}
		}

		// Check if all junctions have the same group
		int firstGroup = groups[0];
		int foundDiff = false;
		for (auto grp: groups) {
			if (grp == -1 || grp != firstGroup) {
				foundDiff = true;
				break;
			}
		}
		if (!foundDiff) {
			cout << conn.x1 << " " << conn.x2 << endl;
			int64_t x1 = conn.x1;
			int64_t x2 = conn.x2;
			cout << x1 * x2 << endl;
			break;
		}
	}

	// for (auto grp: groups) {
	// 	cout << grp << " ";
	// }
	// cout << endl;

	// for (auto grp: groups) {
	// 	if (grp > -1) sizes[grp]++;
	// }

	// for (auto size: sizes) {
	//  	cout << size << " ";
	// }
	// cout << endl;

	// sort(begin(sizes), end(sizes), greater<int>());
	
	// cout << sizes[0] * sizes[1] * sizes[2] << endl;

	return 0;
}
