#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int searchPathsToOut(string currNode, unordered_map<string, vector<string>> *outgoing, unordered_map<string, int> *memo) {
	if ((*memo).contains(currNode)) return (*memo)[currNode];

	int pathCount = 0;
	for (auto s: (*outgoing)[currNode]) {
		pathCount += searchPathsToOut(s, outgoing, memo);
	}
	(*memo)[currNode] = pathCount;

	return pathCount;
}

int main() {
	unordered_map<string, vector<string>> outgoing;
	unordered_map<string, int> pathsToOut;
	pathsToOut["out"] = 1;

	for (string line; getline(cin, line);) {
		string currString = "";
		bool parsingOutputs = false;
		string startNode = "";
		for (char c: line) {
			if (!parsingOutputs) {
				if (c == ':') {
					parsingOutputs = true;
					outgoing[startNode] = vector<string>();
				} else {
					startNode.append(1, c);
				}
			} else {
				if (c == ' ' && currString != "") {
					outgoing[startNode].push_back(currString);
					currString = "";
				} else if (c != ' ') {
					currString.append(1, c);
				}
			}
		}
		outgoing[startNode].push_back(currString);
	}

	// for (auto [k, v]: outgoing) {
	//  	cout << k << ": ";
	//  	for (auto s: v) {
	//  		cout << s << " ";
	//  	}
	//  	cout << endl;
	// }

	cout << searchPathsToOut("you", &outgoing, &pathsToOut) << endl;

	return 0;
}
