#include <iostream>
#include <string>
#include <unordered_map>
#include <stdint.h>

using namespace std;

int64_t searchPathsToTarget(string currNode, unordered_map<string, vector<string>> *outgoing, unordered_map<string, int> *memo, string target) {
	if (currNode == target) return 1;
	if ((*memo).contains(currNode)) return (*memo)[currNode];

	int64_t pathCount = 0;
	for (auto s: (*outgoing)[currNode]) {
		pathCount += searchPathsToTarget(s, outgoing, memo, target);
	}
	(*memo)[currNode] = pathCount;

	return pathCount;
}

int main() {
	unordered_map<string, vector<string>> outgoing;

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

	// Technically, only 1 of the following blocks will yield a non-zero result since we have a DAG
	unordered_map<string, int> memo1;
	unordered_map<string, int> memo2;
	unordered_map<string, int> memo3;
	int64_t startToFft = searchPathsToTarget("svr", &outgoing, &memo1, "fft");
	int64_t fftToDac = searchPathsToTarget("fft", &outgoing, &memo2, "dac");
	int64_t dacToOut = searchPathsToTarget("dac", &outgoing, &memo3, "out");

	unordered_map<string, int> memo4;
	unordered_map<string, int> memo5;
	unordered_map<string, int> memo6;
	int64_t startToDac = searchPathsToTarget("svr", &outgoing, &memo4, "dac");
	int64_t dacToFft = searchPathsToTarget("dac", &outgoing, &memo5, "fft");
	int64_t fftToOut = searchPathsToTarget("fft", &outgoing, &memo6, "out");

	cout << startToFft * fftToDac * dacToOut + startToDac * dacToFft * fftToOut << endl;

	return 0;
}
