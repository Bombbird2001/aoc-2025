#include <iostream>
#include <string>

using namespace std;

int getJoltage(string line) {
	int no1 = -1;
	int index1 = -1;
	int no2 = -1;

	for (int i = 0; i < line.length() - 1; i++) {
		int currNo = line[i] - '0';
		if (currNo > no1) {
			no1 = currNo;
			index1 = i;
		}
	}

	for (int i = line.length() - 1; i > index1; i--) {
		int currNo = line[i] - '0';
		if (currNo > no2) {
			no2 = currNo;
		}
	}

	return no1 * 10 + no2;
}

int main() {
	int sum = 0;

	for (string line; getline(cin, line);) {
		sum += getJoltage(line);
	}

	cout << sum << endl;

	return 0;
}
