#include <bits/stdc++.h>
using namespace std;

// 변환 행렬 계산 구현 있다 치고
class Transform
{
public:
	static Transform origin();
	Transform combine(Transform& other);
};

//
class GraphNode
{
public:
	GraphNode(Mesh* mest)
		: mesh_(mesh),
		local_(Transform::origin()),
		dirty_(true)
	{}

	void renderMesh(Mesh* mesh, Transform transform);

	void render(Transform parentWorld, bool dirty)
	{
		dirty |= dirty_;
		if (dirty)
		{
			world_ = local_.combine(parentWorld);
			dirty_ = false;
		}
	}

	void setTransform(Transform local)
	{
		local_ = local;
		dirty_ = true;
	}

private:
	Transform world_;
	bool dirty_;
	Transform local_;
	Mesh* mesh_;
	GraphNode* children_[MAX_CHILDREN];
	int numChildren;
};

int main()
{
	GraphNode* graph_ = new GraphNode(nullptr);
	graph_->render(Transform::origin());
}