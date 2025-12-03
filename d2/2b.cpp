#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>

using namespace std;

bool isInvalid(int64_t value, int digitCount, int64_t *pow10Array) {
	for (int i = 2; i <= digitCount; i++) {
		if (digitCount % i != 0) {
			continue;
		}

		int64_t factor = pow10Array[digitCount / i];
		// cout << value << " " << digitCount << " " << factor << endl;
		
		int64_t repeated = value % factor;
		int64_t tmpValue = value / factor;
		bool noMatch = false;
		for (int j = 0; j < i - 1; j++) {
			if (tmpValue % factor != repeated) {
				noMatch = true;
				break;
			}
			tmpValue /= factor;
		}
		if (!noMatch) return true;
	}

	return false;
}

int64_t invalidSum(int64_t start, int64_t end, int64_t placeValue, int digitCount, int64_t *pow10Array) {
	int64_t sum = 0;

	while (start <= end) {
		if (start >= placeValue * 10) {
			placeValue *= 10;
			digitCount++;
		}

		if (isInvalid(start, digitCount, pow10Array)) {
			sum += start;
			// cout << "Added " << start << endl;
		}

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

	int64_t *pow10Array = new int64_t[19];
	int64_t counter = 1;
	for (int i = 0; i <= 18; i++) {
		pow10Array[i] = counter;
		counter *= 10;
	}

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
				sum += invalidSum(no1, no2, pv1 / 10, digitCount1, pow10Array);
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
	sum += invalidSum(no1, no2, pv1 / 10, digitCount1, pow10Array);

	delete [] pow10Array;

	cout << sum << endl;

	return 0;
}
