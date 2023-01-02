#include <iostream>
using namespace std;

// 지정 초기화

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
	// - 직접 만든 생성자가 없음
	// - 가상 함수 없음
	// - private / protected / static 아닌 데이터 변수는 x
	// Pos3D pos{ 1,2,3 };
	// Pos3D pos{ .z = 2, .x = 3 }; // 순서 맞춰야 함
	Pos3D pos{ .x = 2, .z = 3 };
	// Pos3D pos2{ .x = 2, .z = 3.2f };	// 축소 변환 (narrowing conversion) 시 에러

	Pos2D pos3{ .y = 2 };
}