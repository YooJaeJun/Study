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

// 유니티 코루틴
// - C#에 있는 코루틴 문법을 유니티에서 적극적으로 채용해서 제공

void VeryDifficultFunction()
{
	static int lastIndex = 0;

	for (int i = 0; i < 10000; i++)
	{
		// 매우 복잡한 연산 (A*)

	}
}

// 몬스터 잡으면 -> 아이템이 인벤토리에 들어온다.
// 1. 몬스터를 잡음
// 2. DB 먼저 적용
// 3. 아이템 생성 + 인벤토리에 추가
void KillManager()
{
	// DB에 아이템 생성 요청
	// 
	// -- DB 처리 --
	// 
}

void KillMonster_Item()
{
	// 아이템 생성
	// 인벤토리에 아이템 추가
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

	// 함수가 코루틴이 되려면...
	// - co_return
	// - co_yield
	// - co_await

	// 코루틴을 사용할 수 있는 Framework를 제공한다...
	// 3가지 요소로 구성. (1, 2번에 주목)
	// - promise 객체
	// - 코루틴 핸들 (밖에서 코루틴을 resume / destroy 할 때 사용. 일종의 리모컨)
	// - 코루틴 프레임 (promise 객체. 코루틴이 인자 등을 포함하는 heap 할당 객체)


	// 의사 코드
	/*
	{
		Promise prom : (get_return_object)
		co_await prom.initial)suspend()
		try
		{
			// co_return, co_yield, co_await를 포함하는 코드
		}
		catch (...)
		{
			prom.unhandled_exception();
		}
		co_await prom.final_suspend();
	}
	*/

	// co_await 플로우
	/*
	{
	}
	*/

	auto future = CreateFuture();

	// TODO: 다른 걸 하다..
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
