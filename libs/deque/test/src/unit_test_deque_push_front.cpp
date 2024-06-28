/**
 *	@file	unit_test_deque_push_front.cpp
 *
 *	@brief	push_front のテスト
 *
 *	void push_front(const T& x);
 *	void push_front(T&& x);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace push_front_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().push_front(hamon::declval<T const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().push_front(hamon::declval<T&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().push_front(hamon::declval<T const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().push_front(hamon::declval<T&&>())), "");

	{
		Deque v;
		VERIFY(v.size() == 0);

		T const x(10);
		v.push_front(x);
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		v.push_front(20);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 10);

		v.push_front(30);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 30);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 10);

		v.push_front(40);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 40);
		VERIFY(v[1] == 30);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);

		v.push_front(50);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 50);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 10);

		v.push_front(60);
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 60);
		VERIFY(v[1] == 50);
		VERIFY(v[2] == 40);
		VERIFY(v[3] == 30);
		VERIFY(v[4] == 20);
		VERIFY(v[5] == 10);

		v.push_front(70);
		v.push_front(80);
		v.push_front(90);
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 90);
		VERIFY(v[1] == 80);
		VERIFY(v[2] == 70);
		VERIFY(v[3] == 60);
		VERIFY(v[4] == 50);
		VERIFY(v[5] == 40);
		VERIFY(v[6] == 30);
		VERIFY(v[7] == 20);
		VERIFY(v[8] == 10);
	}
#if 0
	{
		Deque v{1,2,3};
		v.reserve(4);
		// メモリの再確保が行われないときは、end()以外のイテレータは無効にならない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto const it3 = v.begin() + 2;
		v.push_front(10);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(it3 == v.begin() + 2);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 10);
	}
#endif

	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy() : value(13)
	{
	}

	ThrowOnCopy(int v) : value(v)
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw Exception{};
	}

	ThrowOnCopy(ThrowOnCopy&& other) noexcept
		: value(other.value)
	{
	}
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove() : value(14)
	{
	}

	ThrowOnMove(int v) : value(v)
	{
	}

	ThrowOnMove(ThrowOnMove const& other)
		: value(other.value)
	{
	}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}
};
#endif

GTEST_TEST(DequeTest, PushFrontTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<int>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<unsigned char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::deque<ThrowOnCopy> v;

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.push_front(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v(2);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.push_front(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ( 2, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ(13, v[2].value);
	}
#if 0
	{
		hamon::deque<ThrowOnCopy> v(2);
		v.reserve(10);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_front(t), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.push_front(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
#endif
	{
		hamon::deque<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.push_front(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ(14, v[3].value);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		EXPECT_THROW(v.push_front(ThrowOnMove(2)), ThrowOnMove::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ(14, v[3].value);
	}
#if 0
	{
		hamon::deque<ThrowOnMove> v(3);
		v.reserve(10);

		ThrowOnMove const t(1);
		v.push_front(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.push_front(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
#endif
#endif
}

}	// namespace push_front_test

}	// namespace hamon_deque_test
