#include <iostream>
#include <vector>
using namespace std;

struct node {
	char val;
	char left;
	char right;
	node() : val('.'), left('.'), right('.') {}
	node(char v, char l, char r) : val(v), left(l), right(r) {}
};
vector<node> nodes(26);

struct tree {
	char root;
	tree(char ch) : root(ch) {}

	void postorder() { postorder(root); }
	void postorder(char ch) {
		if (ch != '.') {
			postorder(nodes[ch - 'A'].left);
			postorder(nodes[ch - 'A'].right);
			cout << nodes[ch - 'A'].val;
		}
	}

	void inorder() { inorder(root); }
	void inorder(char ch) {
		if (ch != '.') {
			inorder(nodes[ch - 'A'].left);
			cout << nodes[ch - 'A'].val;
			inorder(nodes[ch - 'A'].right);
		}
	}

	void preorder() { preorder(root); }
	void preorder(char ch) {
		if (ch != '.') {
			cout << nodes[ch - 'A'].val;
			preorder(nodes[ch - 'A'].left);
			preorder(nodes[ch - 'A'].right);
		}
	}
};

void solution() {
	int n;
	cin >> n;
	for (int i = 0; i != n; i++) {
		char c1, c2, c3;
		cin >> c1 >> c2 >> c3;
		nodes[c1 - 'A'].val = c1;
		nodes[c1 - 'A'].left = c2;
		nodes[c1 - 'A'].right = c3;
	}
	tree t(nodes[0].val);
	t.preorder();
	cout << '\n';
	t.inorder();
	cout << '\n';
	t.postorder();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int testCaseNum = 1;
	//cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}