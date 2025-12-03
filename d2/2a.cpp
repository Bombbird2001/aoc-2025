#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>

using namespace std;

int64_t invalid_sum(int64_t start, int64_t end, int64_t placeValue, int digitCount) {
	int64_t factor = 1;
	for (int i = 0; i < digitCount / 2; i++) {
		factor *= 10;
	}

	int64_t sum = 0;

	while (start <= end) {
		if (start >= placeValue * 10) {
			placeValue *= 10;
			digitCount++;
			if (digitCount % 2 == 0) {
				factor *= 10;
			}
		}

		if (digitCount % 2 == 1) {
			start = placeValue * 10;
			continue;
		}

		if (start / factor == start % factor) sum += start;

		start++;
	}

	return sum;
}

int main() {
	int64_t no1 = 0;
	int64_t pv1 = 1;
	int64_t digitCount1 = 0;
	int64_t no2 = 0;
	int64_t pv2 = 1;

	int64_t sum = 0;

	for (string line; getline(cin, line);) {
		bool isNo1 = false;
		for (int x = line.length() - 1; x >= 0; x--) {
			char c = line[x];
			if (c == '-') {
				if (isNo1) throw invalid_argument("Expected isNo1 to be false");
				isNo1 = true;
			} else if (c == ',') {
				if (!isNo1) throw invalid_argument("Expected isNo1 to be true");
				isNo1 = false;
				sum += invalid_sum(no1, no2, pv1 / 10, digitCount1);
				no1 = 0;
				no2 = 0;
				pv1 = 1;
				pv2 = 1;
				digitCount1 = 0;
			} else {
				if (isNo1) {
					no1 += pv1 * (c - '0');
					pv1 *= 10;
					digitCount1++;
				} else {
					no2 += pv2 * (c - '0');
					pv2 *= 10;
				}
			}
		} 
	}

	// cout << no1 << " " << no2 << " " << pv1 << " " << digitCount1 << endl;
	sum += invalid_sum(no1, no2, pv1 / 10, digitCount1);

	cout << sum << endl;

	return 0;
}
