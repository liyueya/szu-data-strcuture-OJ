#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

struct huffmannode {
	int weight;
	int parent;
	int lchild;
	int rchild;
};

void select(const vector<huffmannode>& huffmantree, int n, int& s1, int& s2) {
	int min1 = 0x3f3f3f3f, min2 = 0x3f3f3f3f;
	s1 = s2 = 0;

	for (int i = 1; i <= n; i++) {
		if (huffmantree[i].parent == 0) {
			if (huffmantree[i].weight < min1) {
				min2 = min1;
				s2 = s1;
				min1 = huffmantree[i].weight;
				s1 = i;
			}
			else if (huffmantree[i].weight < min2) {
				min2 = huffmantree[i].weight;
				s2 = i;
			}
		}
	}
	if (s1 > 0 && s2 > 0 && huffmantree[s1].weight > huffmantree[s2].weight) {
		swap(s1, s2);
	}
}

void buildhuffmantree(vector<huffmannode>& huffmantree, const vector<int>& weights) {
	int n = weights.size();
	int m = 2 * n - 1;
	huffmantree.resize(m + 1);
	for (int i = 1; i <= n; i++) {
		huffmantree[i].weight = weights[i - 1];
		huffmantree[i].parent = 0;
		huffmantree[i].lchild = 0;
		huffmantree[i].rchild = 0;
	}
	for (int i = n + 1; i <= m; i++) {
		huffmantree[i].weight = 0;
		huffmantree[i].parent = 0;
		huffmantree[i].lchild = 0;
		huffmantree[i].rchild = 0;
	}
	for (int i = n + 1; i <= m; i++) {
		int s1, s2;
		select(huffmantree, i - 1, s1, s2);
		huffmantree[i].lchild = s1;
		huffmantree[i].rchild = s2;
		huffmantree[i].weight = huffmantree[s1].weight + huffmantree[s2].weight;
		huffmantree[s1].parent = i;
		huffmantree[s2].parent = i;
	}
}

vector<string> gethuffmancode(const vector<huffmannode>& huffmantree, int n) {
	vector<string> huffmancode(n + 1);
	for (int i = 1; i <= n; i++) {
		string code = "";
		int current = i;
		int parent = huffmantree[i].parent;
		while (parent != 0) {
			if (huffmantree[parent].lchild == current) {
				code = "0" + code;
			}
			else {
				code = "1" + code;
			}
			current = parent;
			parent = huffmantree[parent].parent;
		}
		huffmancode[i] = code;
	}
	return huffmancode;
}

int main() {
	int n;
	cin >> n;
	vector<int> weights(n);
	for (int i = 0; i < n; i++) {
		cin >> weights[i];
	}
	vector<huffmannode> huffmantree;
	buildhuffmantree(huffmantree, weights);
	vector<string> huffmancode = gethuffmancode(huffmantree, n);
	for (int i = 1; i <= n; i++) {
		cout << huffmantree[i].weight << "-" << huffmancode[i] << endl;
	}
	return 0;
}
