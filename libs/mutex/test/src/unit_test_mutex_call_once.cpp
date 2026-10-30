/**
 *	@file	unit_test_mutex_call_once.cpp
 *
 *	@brief	call_once のテスト
 *
 *	template<class Callable, class... Args>
 *	void call_once(once_flag& flag, Callable&& func, Args&&... args);
 */

#include <hamon/mutex/call_once.hpp>
#include <hamon/mutex/once_flag.hpp>
#include <hamon/chrono.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_call_once_test
{

typedef hamon::chrono::milliseconds ms;

hamon::once_flag flg0;

int init0_called = 0;

void init0()
{
	hamon::this_thread::sleep_for(ms(10));
	++init0_called;
}

void f0()
{
	hamon::call_once(flg0, init0);
}

hamon::once_flag flg3;

int init3_called = 0;
int init3_completed = 0;

#if !defined(HAMON_NO_EXCEPTIONS)
void init3()
{
	++init3_called;
	hamon::this_thread::sleep_for(ms(10));
	if (init3_called == 1)
	{
		throw 1;
	}
	++init3_completed;
}

void f3()
{
	try
	{
		hamon::call_once(flg3, init3);
	}
	catch (...)
	{
	}
}
#endif

struct init1
{
	static int called;

	void operator()(int i) { called += i; }
};

int init1::called = 0;

hamon::once_flag flg1;

void f1()
{
	hamon::call_once(flg1, init1(), 1);
}

struct init2
{
	static int called;

	void operator()(int i, int j) const { called += i + j; }
};

int init2::called = 0;

hamon::once_flag flg2;

void f2()
{
	hamon::call_once(flg2, init2(), 2, 3);
	hamon::call_once(flg2, init2(), 4, 5);
}

hamon::once_flag flg41;
hamon::once_flag flg42;

int init41_called = 0;
int init42_called = 0;

void init42();

void init41()
{
	hamon::this_thread::sleep_for(ms(10));
	++init41_called;
}

void init42()
{
	hamon::this_thread::sleep_for(ms(10));
	++init42_called;
}

void f41()
{
	hamon::call_once(flg41, init41);
	hamon::call_once(flg42, init42);
}

void f42()
{
	hamon::call_once(flg42, init42);
	hamon::call_once(flg41, init41);
}

class MoveOnly
{
public:
	MoveOnly() {}
	MoveOnly(MoveOnly&&) {}
	MoveOnly(const MoveOnly&) = delete;

	void operator()(MoveOnly&&) {}
};

class NonCopyable
{
public:
	NonCopyable() {}
	NonCopyable(const NonCopyable&) = delete;

	void operator()(int&) {}
};

// reference qualifiers on functions are a C++11 extension
struct RefQual
{
	int lv_called, rv_called;

	RefQual() : lv_called(0), rv_called(0) {}

	void operator()()& { ++lv_called; }
	void operator()()&& { ++rv_called; }
};

GTEST_TEST(CallOnceTest, CallOnceTest)
{
	// check basic functionality
	{
		hamon::thread t0(f0);
		hamon::thread t1(f0);
		t0.join();
		t1.join();
		EXPECT_TRUE(init0_called == 1);
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	// check basic exception safety
	{
		hamon::thread t0(f3);
		hamon::thread t1(f3);
		t0.join();
		t1.join();
		EXPECT_TRUE(init3_called == 2);
		EXPECT_TRUE(init3_completed == 1);
	}
#endif
	// check deadlock avoidance
	{
		hamon::thread t0(f41);
		hamon::thread t1(f42);
		t0.join();
		t1.join();
		EXPECT_TRUE(init41_called == 1);
		EXPECT_TRUE(init42_called == 1);
	}
	// check functors with 1 arg
	{
		hamon::thread t0(f1);
		hamon::thread t1(f1);
		t0.join();
		t1.join();
		EXPECT_TRUE(init1::called == 1);
	}
	// check functors with 2 args
	{
		hamon::thread t0(f2);
		hamon::thread t1(f2);
		t0.join();
		t1.join();
		EXPECT_TRUE(init2::called == 5);
	}
	{
		hamon::once_flag f;
		hamon::call_once(f, MoveOnly(), MoveOnly());
	}
	// check LWG2442: call_once() shouldn't DECAY_COPY()
	{
		hamon::once_flag f;
		int i = 0;
		hamon::call_once(f, NonCopyable(), i);
	}
	// reference qualifiers on functions are a C++11 extension
	{
		hamon::once_flag f1, f2;
		RefQual rq;
		hamon::call_once(f1, rq);
		EXPECT_TRUE(rq.lv_called == 1);
		hamon::call_once(f2, hamon::move(rq));
		EXPECT_TRUE(rq.rv_called == 1);
	}
}

}	// namespace hamon_call_once_test
