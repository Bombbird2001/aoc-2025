#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

struct maxNoIndex {
	int index;
	int maxNo;
};

maxNoIndex getLargestNoBetweenIndexIncl(string line, int startIndex, int endIndex) {
	// cout << startIndex << " " << endIndex << endl;

	maxNoIndex noIndex;
	noIndex.index = -1;
	noIndex.maxNo = -1;

	for (int i = startIndex; i <= endIndex; i++) {
		int currNo = line[i] - '0';
		if (currNo > noIndex.maxNo) {
			noIndex.index = i;
			noIndex.maxNo = currNo;
		}
	}

	return noIndex;
}

int64_t getJoltageBig(string line, int64_t *pow10Array) {
	int64_t sum = 0;

	int startIndexTracker = 0;
	for (int i = 11; i >= 0; i--) {
		maxNoIndex res = getLargestNoBetweenIndexIncl(line, startIndexTracker, line.length() - 1 - i);
		sum += res.maxNo * pow10Array[i];
		startIndexTracker = res.index + 1;
	}

	return sum;
}

int main() {
	int64_t sum = 0;

	int64_t *pow10Array = new int64_t[12];
	pow10Array[0] = 1;
	for (int i = 1; i < 12; i++) {
		pow10Array[i] = 10 * pow10Array[i - 1];
	}

	for (string line; getline(cin, line);) {
		sum += getJoltageBig(line, pow10Array);
	}

	cout << sum << endl;

	return 0;
}
