#include <iostream>
#include <string>

using namespace std;

int main() {
	int64_t totalPresses = 0;

	int powerTable[20] = {1};
	for (int i = 1; i < 20; i++) {
		powerTable[i] = 2 * powerTable[i - 1];
	}

	for (string line; getline(cin, line);) {
		int parsePhase = 0;
		int possibleStates = 1;
		int requiredState = 0;
		vector<vector<int>> buttons;
		int currNo = 0;
		int pv = 1;
		
		for (auto c: line) {
			if (c == ' ') continue;
			if (c == '{') parsePhase = 2;
			if (parsePhase == 0) {
				if (c == '[') continue;
				if (c == '#') {
					possibleStates *= 2;
					requiredState += pv;
					pv *= 2;
				} else if (c == '.') {
					possibleStates *= 2;
					pv *= 2;
				} else if (c == ']') parsePhase++;
			} else if (parsePhase == 1) {
				if (c == '(') buttons.push_back(vector<int>());
				else if (c == ',' || c == ')') {
					buttons.back().push_back(currNo);
					currNo = 0;
				} else {
					currNo *= 10;
					currNo += (c - '0');
				}
			}
		}

		// Ignore phase 2 for now
		// cout << "Target on: " << requiredState << endl;
		// cout << "Total states: " << possibleStates << endl;
		// for (auto i: needsOn) {
		// 	cout << i << " ";
		// }
		// cout << endl;

		// cout << "Buttons" << endl;
		// for (auto v: buttons) {
		// 	for (auto i: v) {
		// 		cout << i << " ";
		// 	}
		// 	cout << endl;
		// }

		// Max number of states is small (2^10 or 2^11?), just keep track of states using an array, indexed by the binary representation of whether lights are on
		vector<bool> visitedStates(possibleStates, false);
		queue<int> bfsQueue;
		bfsQueue.push(0);
		queue<int> pendingQueue;
		int steps = 0;
		while (!bfsQueue.empty()) {
			int currState = bfsQueue.front();
			bfsQueue.pop();
			if (currState == requiredState) break;
			for (auto button: buttons) {
				int xorValue = 0;
				for (auto i: button) {
					xorValue += powerTable[i];
				}
				int nextState = currState ^ xorValue;
				if (visitedStates[nextState]) continue;
				visitedStates[nextState] = true;
				pendingQueue.push(nextState);
			}
			if (bfsQueue.empty()) {
				bfsQueue = pendingQueue;
				pendingQueue = queue<int>();
				steps++;
			}
		}

		totalPresses += steps;
		// cout << "Target state: " << requiredState << endl;
		// cout << steps << endl;
	}

	cout << totalPresses << endl;

	return 0;
}
