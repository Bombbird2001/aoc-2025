#include <iostream>
#include <string>

using namespace std;

int main() {
	int pos = 50;
	int times = 0;

	for (string line; getline(cin, line);) {
		char direction = line[0];
		int turns = stoi(line.substr(1));
		int full_rots = turns / 100;
		if (direction == 'L') turns *= -1;
		int partial_rots = turns % 100;
		if ((pos > 0 && pos + partial_rots <= 0) || (pos < 0 && pos + partial_rots >= 0) || (pos / 100 != (pos + partial_rots) / 100)) times++;
		times += full_rots;
		pos = (pos + turns) % 100;
		if (pos < 0) pos += 100;
	}

	cout << times << endl;

	return 0;
}
