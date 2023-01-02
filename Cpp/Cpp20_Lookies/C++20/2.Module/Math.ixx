module;	// global module fragment

// ���� �ܺ� ��� �߰�
#include <vector>


// module ����
export module math;

// import module ...

// submodule
// math.time�� import�ؼ� �ٽ� math ��⿡ �����ؼ� export
export import math.time;

// 1) �Լ� �տ��ٰ� export
export int Add(int a, int b)
{
	return a + b;
}

// 2) export�ϰ� ���� �ֵ��� ���� �����ִ�
export
{
	void TestExport()
	{

	}
}

// 3) namespace�� ���� -> ����
// ���ο����� ����ϴ� �Լ��� ���ӽ����̽� �ۿ� ����.
void Internal() {}

export namespace math
{
	void TestExport2()
	{

	}
}