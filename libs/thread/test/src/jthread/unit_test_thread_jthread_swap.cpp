/**
 *	@file	unit_test_thread_jthread_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(jthread&) noexcept;
 *
 *	friend void swap(jthread& lhs, jthread& rhs) noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace swap_test
{

GTEST_TEST(JThreadTest, SwapTest)
{
	// this is default constructed
	{
		hamon::jthread t1;
		hamon::jthread t2([] {});

		static_assert(noexcept(t1.swap(t2)), "");
		static_assert(hamon::is_same_v<decltype(t1.swap(t2)), void>, "");
		static_assert(noexcept(swap(t1, t2)), "");
		static_assert(hamon::is_same_v<decltype(swap(t1, t2)), void>, "");

		const auto originalId2 = t2.get_id();
		t1.swap(t2);

		EXPECT_TRUE(t1.get_id() == originalId2);
		EXPECT_TRUE(t2.get_id() == hamon::jthread::id());

		swap(t1, t2);

		EXPECT_TRUE(t1.get_id() == hamon::jthread::id());
		EXPECT_TRUE(t2.get_id() == originalId2);
	}

	// that is default constructed
	{
		hamon::jthread t1([] {});
		hamon::jthread t2{};
		const auto originalId1 = t1.get_id();
		t1.swap(t2);

		EXPECT_TRUE(t1.get_id() == hamon::jthread::id());
		EXPECT_TRUE(t2.get_id() == originalId1);
	}

	// both not default constructed
	{
		hamon::jthread t1([] {});
		hamon::jthread t2([] {});
		const auto originalId1 = t1.get_id();
		const auto originalId2 = t2.get_id();
		t1.swap(t2);

		EXPECT_TRUE(t1.get_id() == originalId2);
		EXPECT_TRUE(t2.get_id() == originalId1);
	}

	// both default constructed
	{
		hamon::jthread t1;
		hamon::jthread t2;
		t1.swap(t2);

		EXPECT_TRUE(t1.get_id() == hamon::jthread::id());
		EXPECT_TRUE(t2.get_id() == hamon::jthread::id());
	}
}

}	// namespace swap_test

}	// namespace hamon_jthread_test
