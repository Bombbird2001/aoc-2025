#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h>

using namespace std;

struct range {
	int64_t start;
	int64_t end;
};

bool comp(range r1, range r2) {
	if (r1.start < r2.start) return true;
	if (r1.start > r2.start) return false;
	
	// We want larger ends behind smaller ends if starts are equal
	if (r1.end <= r2.end) return true;

	return false;
}

int main() {
	vector<range> ranges;
	vector<int64_t> items;

	bool loadingItems = false;
	for (string line; getline(cin, line);) {
		if (line.empty()) {
			loadingItems = true;
			continue;
		}

		if (loadingItems) {
			int64_t no = 0;
			int64_t pv = 1;
			for (int i = line.length() - 1; i >= 0; i--) {
				no += (line[i] - '0') * pv;
				pv *= 10;
			}
			items.push_back(no);
			continue;
		}

		range range;
		
		int64_t no1 = 0;
		int64_t no2 = 0;
		bool isNo1 = false;
		int64_t pv = 1;
		for (int i = line.length() - 1; i >= 0; i--) {
			char c = line[i];
			if (c == '-') {
				isNo1 = true;
				pv = 1;
				continue;
			}
			int64_t toAdd = (c - '0') * pv;
			if (isNo1) no1 += toAdd;
			else no2 += toAdd;

			pv *= 10;
		}

		range.start = no1;
		range.end = no2;
		ranges.push_back(range);
	}

	sort(ranges.begin(), ranges.end(), comp);

	// Merge overlapping ranges
	vector<range> combinedRange;
	for (auto r: ranges) {
		if (combinedRange.empty() || combinedRange.back().end < r.start) {
			combinedRange.push_back(r);
		} else if (r.end > combinedRange.back().end) {
			combinedRange.back().end = r.end;
		}
	}

	int64_t totalFreshCount = 0;
	for (auto r: combinedRange) {
		totalFreshCount += r.end - r.start + 1;
	}

	cout << totalFreshCount << endl;

	return 0;
}
