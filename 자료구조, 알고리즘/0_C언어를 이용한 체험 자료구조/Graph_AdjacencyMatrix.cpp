#include <iostream>
using namespace std;

enum class GraphType
{
	directed,
	undirected
};
const int maxSize = 6;

template <typename T>
class Graph
{
private:
	GraphType mode;
	T adjMatrix[maxSize][maxSize];
	bool nodeList[maxSize];
	int nodeSize;

public:
	Graph() = default;

	Graph(const GraphType mode)
		: mode(mode), nodeSize(0)
	{
		int r, c;
		for (int r = 0; r < maxSize; r++)
		{
			nodeList[r] = false;
			for (int c = 0; c < maxSize; c++)
			{
				adjMatrix[r][c] = false;
			}
		}
	}

	bool CheckNode(int node)
	{
		if (node >= maxSize)
		{
			cout << "Error: node no out of range.\n";
			return false;
		}
		return true;
	}

	void insertNode(int node)
	{
		if (!CheckNode(node)) return;
		nodeList[node] = true;
		nodeSize++;
	}

	void deleteNode(int node)
	{
		if (!CheckNode(node)) return;

		for (int i = 0; i < nodeSize; i++)
		{
			deleteEdge(i, node);
			deleteEdge(node, i);
		}

		nodeList[node] = false;
		if (node == nodeSize - 1) nodeSize--;
	}


	bool CheckEdge(T from, T to)
	{
		if (from < 0 || from >= maxSize || to < 0 || to >= maxSize)
		{
			cout << "Error: node no out of range.\n";
			return false;
		}
		return true;
	}

	void insertEdge(T from, T to)
	{
		if (!CheckEdge(from, to)) return;
		adjMatrix[from][to] = true;
		if (mode == GraphType::undirected) adjMatrix[to][from] = true; // 양방향 에지
	}

	void deleteEdge(T from, T to)
	{
		if (!CheckEdge(from, to)) return;
		adjMatrix[from][to] = false;
		if (mode == GraphType::undirected) adjMatrix[to][from] = false; // 양방향 에지
	}

	T getNodeSize()
	{
		int count = 0;
		for (int n = 0; n < nodeSize; n++)
		{
			if (nodeList[n]) count++;
		}
		return count;
	}

	T getEdgeSize()
	{
		int count = 0;
		for (int r = 0; r < nodeSize; r++)
		{
			for (int c = 0; c < nodeSize; c++)
			{
				if (adjMatrix[r][c]) count++;
			}
		}
		return count;
	}

	void print()
	{
		cout << "Graph Print\n";
		for (int r = 0; r < nodeSize; r++)
		{
			for (int c = 0; c < nodeSize; c++)
			{
				cout << adjMatrix[r][c] << ' ';
			}
			cout << '\n';
		}
	}

	void graphvizPrint()
	{
		string tempMode;
		if (mode == GraphType::directed) tempMode = "->";
		else tempMode = "--";

		for (int r = 0; r < nodeSize; r++)
		{
			if (nodeList[r]) cout << "\t\"" << r << "\";\n";
		}

		for (int r = 0; r < maxSize; r++)
		{
			for (int c = 0; c < maxSize; c++)
			{
				if (adjMatrix[r][c]) cout << "\t\"" << r << "\" " << tempMode << " \"" << c << "\" \n";
			}
		}
	}

	void graphvizDriver()
	{
		if (mode == GraphType::directed) cout << "digraph G {\n";
		else cout << "graph G {\n";

		graphvizPrint();
		cout << "}\n";
	}
};

int main()
{
	Graph<int> g(GraphType::directed);

	g.insertNode(0);
	g.insertNode(1);
	g.insertNode(2);
	g.insertNode(3);
	g.insertNode(4);
	g.insertNode(5);

	g.insertEdge(0, 1);
	g.insertEdge(0, 2);
	g.insertEdge(0, 3);
	g.insertEdge(0, 4);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);
	g.insertEdge(2, 4);
	g.insertEdge(3, 4);

	g.print();
	g.graphvizDriver();

	g.deleteEdge(1, 3);
	g.deleteNode(2);

	g.print();
	g.graphvizDriver();


	Graph<int> g2(GraphType::undirected);

	g2.insertNode(0);
	g2.insertNode(1);
	g2.insertNode(2);
	g2.insertNode(3);
	g2.insertNode(4);
	g2.insertNode(5);

	g2.insertEdge(0, 1);
	g2.insertEdge(0, 4);
	g2.insertEdge(1, 3);
	g2.insertEdge(2, 3);
	g2.insertEdge(2, 4);
	g2.insertEdge(3, 4);

	g2.print();
	g2.graphvizDriver();

	cout << "Node Size : " << g2.getNodeSize() << '\n';
	cout << "Edge Size : " << g2.getNodeSize() << '\n';
	cout << '\n';

	g2.deleteEdge(1, 3);
	g2.deleteNode(2);

	g2.print();
	g2.graphvizDriver();

	cout << "Node Size : " << g2.getNodeSize() << '\n';
	cout << "Edge Size : " << g2.getNodeSize() << '\n';
}
