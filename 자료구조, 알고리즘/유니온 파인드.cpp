#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

vector<int> parent(10);

int Parent(int x)
{
	if (x == parent[x])
		return x;

	return parent[x] = Parent(parent[x]);
}

void Union(int x, int y)
{
	x = Parent(x);
	y = Parent(y);

	if (x < y)
		parent[y] = x;
	else
		parent[x] = y;
}

bool IsUnion(int x, int y)
{
	x = Parent(x);
	y = Parent(y);
	return x == y;
}


int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	for (int i = 0; i < parent.size(); i++)
		parent[i] = i;

	Union(1, 2);
	Union(4, 5);
	Union(2, 6);

	cout << "2¿Í 4 : " << IsUnion(2, 4) << '\n';

	Union(1, 4);

	cout << "2¿Í 4 : " << IsUnion(2, 4) << '\n';

	return 0;
}