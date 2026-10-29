/**
 *	@file	unit_test_thread_thread_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	thread(thread&& x) noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace ctor_move_test
{

static_assert( hamon::is_move_constructible_v<hamon::thread>, "");
static_assert( hamon::is_nothrow_move_constructible_v<hamon::thread>, "");
static_assert(!hamon::is_trivially_move_constructible_v<hamon::thread>, "");
static_assert( hamon::is_implicitly_move_constructible_v<hamon::thread>, "");

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
};

int G::n_alive = 0;
bool G::op_run = false;

GTEST_TEST(ThreadTest, CtorMoveTest)
{
	{
		int x = 0;
		hamon::thread t1([&] { ++x; });
		auto id1 = t1.get_id();
		hamon::thread t2(hamon::move(t1));

		// [thread.thread.constr]/11
		EXPECT_TRUE(t1.get_id() == hamon::thread::id());
		EXPECT_TRUE(t1.get_id() != id1);
		EXPECT_TRUE(t2.get_id() == id1);
		EXPECT_TRUE(t2.get_id() != hamon::thread::id());

		t2.join();

		EXPECT_EQ(1, x);
	}
	{
		EXPECT_EQ(0, G::n_alive);
		EXPECT_FALSE(G::op_run);
		{
			G g;
			EXPECT_EQ(1, G::n_alive);
			EXPECT_FALSE(G::op_run);

			hamon::thread t0(g);
			hamon::thread::id id = t0.get_id();

			hamon::thread t1 = hamon::move(t0);
			EXPECT_TRUE(t1.get_id() == id);
			EXPECT_TRUE(t0.get_id() == hamon::thread::id());

			t1.join();
			EXPECT_EQ(1, G::n_alive);
			EXPECT_TRUE(G::op_run);
		}
		EXPECT_EQ(0, G::n_alive);
		EXPECT_TRUE(G::op_run);
	}
}

}	// namespace ctor_move_test

}	// namespace hamon_thread_test
