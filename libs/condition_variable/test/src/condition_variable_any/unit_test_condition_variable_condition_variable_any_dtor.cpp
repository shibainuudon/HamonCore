/**
 *	@file	unit_test_condition_variable_condition_variable_any_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~condition_variable_any();
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace dtor_test
{

hamon::condition_variable_any* cv;
hamon::mutex m;

bool f_ready = false;
bool g_ready = false;

void f()
{
	m.lock();
	f_ready = true;
	cv->notify_one();
	delete cv;
	m.unlock();
}

void g()
{
	m.lock();
	g_ready = true;
	cv->notify_one();
	while (!f_ready)
	{
		cv->wait(m);
	}
	m.unlock();
}

GTEST_TEST(ConditionVariableAnyTest, DtorTest)
{
	cv = new hamon::condition_variable_any;
	hamon::thread th2(g);
	m.lock();
	while (!g_ready)
	{
		cv->wait(m);
	}
	m.unlock();
	hamon::thread th1(f);
	th1.join();
	th2.join();
}

}	// namespace dtor_test

}	// namespace hamon_condition_variable_any_test
