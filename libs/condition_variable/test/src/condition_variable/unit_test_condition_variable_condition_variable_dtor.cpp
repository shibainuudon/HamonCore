/**
 *	@file	unit_test_condition_variable_condition_variable_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~condition_variable();
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_test
{

namespace dtor_test
{

hamon::condition_variable* cv;
hamon::mutex m;
typedef hamon::unique_lock<hamon::mutex> Lock;

bool f_ready = false;
bool g_ready = false;

void f()
{
	Lock lk(m);
	f_ready = true;
	cv->notify_one();
	delete cv;
}

void g()
{
	Lock lk(m);
	g_ready = true;
	cv->notify_one();
	while (!f_ready)
	{
		cv->wait(lk);
	}
}

GTEST_TEST(ConditionVariableTest, DtorTest)
{
	cv = new hamon::condition_variable;
	hamon::thread th2(g);
	Lock lk(m);
	while (!g_ready)
	{
		cv->wait(lk);
	}
	lk.unlock();
	hamon::thread th1(f);
	th1.join();
	th2.join();
}

}	// namespace dtor_test

}	// namespace hamon_condition_variable_test
