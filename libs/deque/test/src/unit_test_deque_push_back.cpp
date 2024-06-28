/**
 *	@file	unit_test_deque_push_back.cpp
 *
 *	@brief	push_back のテスト
 *
 *	void push_back(const T& x);
 *	void push_back(T&& x);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace push_back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().push_back(hamon::declval<T const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().push_back(hamon::declval<T&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().push_back(hamon::declval<T const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().push_back(hamon::declval<T&&>())), "");

	{
		Deque v;
		VERIFY(v.size() == 0);

		{
			T const x(10);
			v.push_back(x);
		}
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
		{
			auto& r0 = v[0];
			v.push_back(20);
			VERIFY(&r0 == &v[0]);
		}
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			v.push_back(30);
			VERIFY(&r0 == &v[0]);
			VERIFY(&r1 == &v[1]);
		}
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			v.push_back(40);
			VERIFY(&r0 == &v[0]);
			VERIFY(&r1 == &v[1]);
			VERIFY(&r2 == &v[2]);
		}
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.push_back(50);
			VERIFY(&r0 == &v[0]);
			VERIFY(&r1 == &v[1]);
			VERIFY(&r2 == &v[2]);
			VERIFY(&r3 == &v[3]);
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			auto& r4 = v[4];
			v.push_back(60);
			VERIFY(&r0 == &v[0]);
			VERIFY(&r1 == &v[1]);
			VERIFY(&r2 == &v[2]);
			VERIFY(&r3 == &v[3]);
			VERIFY(&r4 == &v[4]);
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
		VERIFY(v[5] == 60);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			auto& r4 = v[4];
			auto& r5 = v[5];
			v.push_back(70);
			v.push_back(80);
			v.push_back(90);
			VERIFY(&r0 == &v[0]);
			VERIFY(&r1 == &v[1]);
			VERIFY(&r2 == &v[2]);
			VERIFY(&r3 == &v[3]);
			VERIFY(&r4 == &v[4]);
			VERIFY(&r5 == &v[5]);
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
		VERIFY(v[5] == 60);
		VERIFY(v[6] == 70);
		VERIFY(v[7] == 80);
		VERIFY(v[8] == 90);
	}

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

GTEST_TEST(DequeTest, PushBackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::deque<ThrowOnCopy> v;

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.push_back(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v(2);

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.push_back(t), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.push_back(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
	{
		hamon::deque<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.push_back(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		EXPECT_THROW(v.push_back(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
#endif
}

}	// namespace push_back_test

}	// namespace hamon_deque_test
