#include <iostream>
using namespace std;

enum class GraphType
{
	directed,
	undirected
};
const int maxSize = 6;

template <typename T>
class Node
{
public:
	T dest;
	Node* next;
	Node() : next(nullptr) {};
	Node(T value) : dest(value), next(nullptr) {}
	~Node()
	{
		if (next) delete next;
		next = nullptr;
	}
};

template <typename T>
class HeadNodes
{
public:
	Node<T>* head;
	int laneNo;
	string name;
	double longitude;
	double latitude;

	HeadNodes() : head(nullptr) {}
	HeadNodes(const int nodeSize) 
	{
		head = new Node<T>(nodeSize);
	}
	~HeadNodes()
	{
		if (head) delete head;
		head = nullptr;
	}
};

template <typename T>
class Graph
{
private:
	int nodeSize;
	GraphType mode;
	HeadNodes<T>* list;

public:
	Graph() = default;

	Graph(const int nodeSize, const GraphType mode)
		: nodeSize(nodeSize), mode(mode)
	{
		list = new HeadNodes<T>(nodeSize);

		for (int i = 0; i < nodeSize; i++)
		{
			list[i].head = nullptr;
		}
	}

	~Graph()
	{
		for (int v = 0; v < nodeSize; v++)
		{
			if (list[v].head) delete list[v].head;
		}
		nodeSize = 0;
		if (list) delete list;
	}

	void insertEdge(int from, int to)
	{
		Node<T>* n = new Node<T>(to);
		n->next = list[from].head;
		list[from].head = n;

		if (mode == GraphType::undirected)
		{
			delete n;
			n = new Node<T>(from);
			n->next = list[to].head;
			list[to].head = n;
		}
	}

	void print()
	{
		for (int v = 0; v < nodeSize; v++)
		{
			Node<T>* n = list[v].head;
			cout << "vertex " << v;
			while (n)
			{
				cout << "-> " << n->dest;
				n = n->next;
			}
			cout << '\n';
		}
	}

	void graphvizPrint()
	{
		string desc;
		if (mode == GraphType::directed) desc = "->";
		else desc = "--";

		for (int v = 0; v < nodeSize; v++)
		{
			cout << "\t\"" << v << "\";\n";
		}

		for (int v = 0; v < nodeSize; v++)
		{
			Node<T>* n = list[v].head;
			while (n)
			{
				cout << "\t\"" << v << "\" " << desc << " \"" << n->dest << "\" \n";
				n = n->next;
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
	Graph<int> g(2, GraphType::directed);

	g.insertEdge(0, 1);
	g.insertEdge(0, 2);
	g.insertEdge(0, 3);
	g.insertEdge(0, 4);
	g.insertEdge(1, 3);
	g.insertEdge(2, 4);

	g.print();
	g.graphvizDriver();
}
