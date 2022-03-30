/*#include <iostream>
#include <vector>
using namespace std;

vector<int> sorted;

void merge(vector<int>& v, int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (v[i] <= v[j]) {
			sorted[k++] = v[i++];
		}
		else {
			sorted[k++] = v[j++];
		}
	}

	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = v[l];
		}
	}
	else {
		for(l = i; l <= mid; l++) {
			sorted[k++] = v[l];
		}
	}

	for (l = left; l <= right; l++) {
		v[l] = sorted[l];
	}
}

void mergeSort(vector<int>& v, int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		mergeSort(v, left, mid);
		mergeSort(v, mid + 1, right);
		merge(v, left, mid, right);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i != n; i++) {
		cin >> v[i];
	}
	
	sorted.resize(n);
	mergeSort(v, 0, n - 1);

	for (auto& elem : v) {
		cout << elem << '\n';
	}

	return 0;
}*/