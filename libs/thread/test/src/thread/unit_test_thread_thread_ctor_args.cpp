/**
 *	@file	unit_test_thread_thread_ctor_args.cpp
 *
 *	@brief	argsを引数に取るコンストラクタのテスト
 *
 *	template<class... Args> explicit thread(Args&&... args);
 */

#include <hamon/thread/thread.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace ctor_args_test
{

class G
{
	int alive_;
public:
	static int n_alive;
	static bool op_run;

	G() : alive_(1) { ++n_alive; }
	G(const G& g) : alive_(g.alive_) { ++n_alive; }
	~G() { alive_ = 0; --n_alive; }

	void operator()()
	{
		EXPECT_EQ(1, alive_);
		EXPECT_TRUE(n_alive >= 1);
		op_run = true;
	}

	void operator()(int i, double j)
	{
		EXPECT_EQ(1, alive_);
		EXPECT_TRUE(n_alive >= 1);
		EXPECT_EQ(5, i);
		EXPECT_EQ(5.5, j);
		op_run = true;
	}
};

int G::n_alive = 0;
bool G::op_run = false;

class MoveOnly
{
public:
	MoveOnly() {}
	MoveOnly(const MoveOnly&) = delete;
	MoveOnly(MoveOnly&&) {}

	void operator()(MoveOnly&&) {}
};

class CopyOnly
{
public:
	CopyOnly() {}
	CopyOnly(const CopyOnly&) = default;
	CopyOnly(CopyOnly&&) = delete;

	void operator()(const CopyOnly&) const {}
};

GTEST_TEST(ThreadTest, CtorArgsTest)
{
	{
		EXPECT_EQ(0, G::n_alive);
		EXPECT_FALSE(G::op_run);
		{
			G g;
			hamon::thread t(g);
			t.join();
		}
		EXPECT_EQ(0, G::n_alive);
		EXPECT_TRUE(G::op_run);
	}
	G::op_run = false;
	{
		EXPECT_EQ(0, G::n_alive);
		EXPECT_FALSE(G::op_run);
		{
			G g;
			hamon::thread t(g, 5, 5.5);
			t.join();
		}
		EXPECT_EQ(0, G::n_alive);
		EXPECT_TRUE(G::op_run);
	}
	{
		hamon::thread t = hamon::thread(MoveOnly(), MoveOnly());
		t.join();
	}
	{
		CopyOnly c;
		hamon::thread t(c, c);
		t.join();
	}
	{
		int x = 0;
		hamon::thread t1([&] { x = 42; });
		int y = 0;
		hamon::thread t2([&](int i) { y = i * 2; }, 13);
		int z = 0;
		hamon::thread t3([&](int a, int b) { z = a + b; }, 2, 3);

		// [thread.thread.constr]/8
		EXPECT_TRUE(t1.get_id() != hamon::thread::id());
		EXPECT_TRUE(t2.get_id() != hamon::thread::id());
		EXPECT_TRUE(t3.get_id() != hamon::thread::id());

		t1.join();
		t2.join();
		t3.join();

		EXPECT_EQ(42, x);
		EXPECT_EQ(26, y);
		EXPECT_EQ( 5, z);
	}
	{
		int x = 0;
		hamon::thread t{
			hamon::thread::stack_size_hint(1234),
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
			hamon::thread::name_hint("TestThread"),
#else
			hamon::thread::name_hint<char>("TestThread"),
#endif
			[&](int a, int b) { x = a * b; },
			3,
			13
		};
		t.join();
		EXPECT_EQ(39, x);
	}
}

}	// namespace ctor_args_test

}	// namespace hamon_thread_test
