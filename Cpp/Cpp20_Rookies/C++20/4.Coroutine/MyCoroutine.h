#pragma once
#include <coroutine>
#include <iostream>
using namespace std;

// 코루틴 객체
template<typename T>
class Future
{
public:
	Future(shared_ptr<T> value) : _value(value) {}
	T get() { return *_value; }

private:
	shared_ptr<T> _value;

public:
	struct promise_type
	{
		Future get_return_object() { return { Future<T>(_ptr)}; }
		void return_value(T value) { *_ptr = value; }
		// suspend_never 절대 멈추지 않고 다음 단계로
		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void unhandled_exception() {}

		// 데이터
		shared_ptr<T> _ptr = make_shared<T>();
	};
};


template<typename T>
class Generator
{
public:
	struct promise_type;
	using handle_type = coroutine_handle<promise_type>;

	Generator(handle_type handle) : _handle(handle)
	{
	}

	~Generator()
	{
		if (_handle)
			_handle.destroy();
	}

	T get() { return _handle.promise()._value; }

	bool next()
	{
		_handle.resume();	 // 중요!
		return !_handle.done();
	}

private:
	handle_type _handle;

public:
	struct promise_type
	{
		Generator<T> get_return_object() { return Generator(handle_type::from_promise(*this)); }
		// suspend_always 멈추고 빠져나와라.
		std::suspend_always initial_suspend() { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		std::suspend_always yield_value(const T value) { _value = value; return {}; }
		std::suspend_always return_void() { return {}; }
		void unhandled_exception() {}

		T _value;
	};
};



class Job
{
public:
	struct promise_type;
	using handle_type = coroutine_handle<promise_type>;

	Job(handle_type handle) : _handle(handle)
	{
	}

	~Job()
	{
		if (_handle)
			_handle.destroy();
	}

	void start()
	{
		if (_handle)
			_handle.resume();
	}

private:
	handle_type _handle;

public:
	struct promise_type
	{
		Job get_return_object() { return Job(handle_type::from_promise(*this)); }
		std::suspend_always initial_suspend() { cout << "Prepare Job" << endl; return {}; }
		std::suspend_never final_suspend() noexcept { cout << "Do Job" << endl; return {}; }
		std::suspend_never return_void() { return {}; }
		void unhandled_exception() {}
	};
};