#include <iostream>
using namespace std;
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <coroutine>
#include "MyCoroutine.h"

// ����Ƽ �ڷ�ƾ
// - C#�� �ִ� �ڷ�ƾ ������ ����Ƽ���� ���������� ä���ؼ� ����

void VeryDifficultFunction()
{
	static int lastIndex = 0;

	for (int i = 0; i < 10000; i++)
	{
		// �ſ� ������ ���� (A*)

	}
}

// ���� ������ -> �������� �κ��丮�� ���´�.
// 1. ���͸� ����
// 2. DB ���� ����
// 3. ������ ���� + �κ��丮�� �߰�
void KillManager()
{
	// DB�� ������ ���� ��û
	// 
	// -- DB ó�� --
	// 
}

void KillMonster_Item()
{
	// ������ ����
	// �κ��丮�� ������ �߰�
}

struct CoroutineObject
{
	struct promise_type
	{
		CoroutineObject get_return_object() { return {}; }
		std::suspend_never initial_suspend() const noexcept { return {}; }
		std::suspend_never final_suspend() const noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
};

CoroutineObject HelloCoroutine()
{
	co_return;
}



Future<int> CreateFuture()
{
	co_return 2022;
}

Generator<int> GenNumbers(int start = 0, int delta = 1)
{
	int now = start;

	while (true)
	{
		co_yield now;	// yield return
		now += delta;
	}
}

Job PrepareJob()
{
	// co_await [Awaitable]
	co_await std::suspend_never();
}

int main()
{
	// 60 fps
	//while (true)
	//{
	//	VeryDifficultFunction();
	//}

	// �Լ��� �ڷ�ƾ�� �Ƿ���...
	// - co_return
	// - co_yield
	// - co_await

	// �ڷ�ƾ�� ����� �� �ִ� Framework�� �����Ѵ�...
	// 3���� ��ҷ� ����. (1, 2���� �ָ�)
	// - promise ��ü
	// - �ڷ�ƾ �ڵ� (�ۿ��� �ڷ�ƾ�� resume / destroy �� �� ���. ������ ������)
	// - �ڷ�ƾ ������ (promise ��ü. �ڷ�ƾ�� ���� ���� �����ϴ� heap �Ҵ� ��ü)


	// �ǻ� �ڵ�
	/*
	{
		Promise prom : (get_return_object)
		co_await prom.initial)suspend()
		try
		{
			// co_return, co_yield, co_await�� �����ϴ� �ڵ�
		}
		catch (...)
		{
			prom.unhandled_exception();
		}
		co_await prom.final_suspend();
	}
	*/

	// co_await �÷ο�
	/*
	{
	}
	*/

	auto future = CreateFuture();

	// TODO: �ٸ� �� �ϴ�..
	cout << future.get() << endl;


	auto numbers = GenNumbers(0, 1);
	for (int i = 0; i < 20; i++)
	{
		numbers.next();
		cout << " " << numbers.get();
	}
	cout << endl;



	auto job = PrepareJob();
	job.start();
}
