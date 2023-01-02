#include <iostream>
using namespace std;

// ���� �ʱ�ȭ

struct Pos2D
{
	int x;
	int y;
};

class Pos3D
{
public:
	// Pos3D() {}
	// Pos3D(int x, int y, int z) : x(x), y(y), z(z) {}
	int x;
	int y;
	int z;
};

int main()
{
	// Aggregate Initialization
	// - ���� ���� �����ڰ� ����
	// - ���� �Լ� ����
	// - private / protected / static �ƴ� ������ ������ x
	// Pos3D pos{ 1,2,3 };
	// Pos3D pos{ .z = 2, .x = 3 }; // ���� ����� ��
	Pos3D pos{ .x = 2, .z = 3 };
	// Pos3D pos2{ .x = 2, .z = 3.2f };	// ��� ��ȯ (narrowing conversion) �� ����

	Pos2D pos3{ .y = 2 };
}