#include <iostream>
#include <string>

using namespace std;

int main() {
	int pos = 50;
	int times = 0;

	for (string line; getline(cin, line);) {
		char direction = line[0];
		int turns = stoi(line.substr(1));
		if (direction == 'L') turns *= -1;
		pos = (pos + turns) % 100;
		if (pos < 0) pos += 100;
		if (pos == 0) times++;
	}

	cout << times << endl;

	return 0;
}
