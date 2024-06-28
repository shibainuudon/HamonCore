/**
 *	@file	unit_test_deque_emplace_front.cpp
 *
 *	@brief	emplace_front のテスト
 *
 *	template<class... Args> reference emplace_front(Args&&... args);
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace emplace_front_test
{

struct MoveOnly
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnly(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly const& x) : value(x.value) {} // = delete;	// TODO Visual Studio 2019 だけ？
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly && x) noexcept : value(x.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly const&) = delete;
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly && x) noexcept { value = x.value; return *this; }
};

struct S
{
	int value;
	HAMON_CXX11_CONSTEXPR S(int x) : value(x) {}
	HAMON_CXX11_CONSTEXPR S(int x, int y) : value(x + y) {}
	HAMON_CXX11_CONSTEXPR S(int x, int y, int z) : value(x + y + z) {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Deque = hamon::deque<T>;
	using Reference = typename Deque::reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().emplace_front()),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().emplace_front(hamon::declval<T>())),
		Reference
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().emplace_front()), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().emplace_front(hamon::declval<T>())), "");

	{
		Deque v{1,2,3};

		// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v.emplace_front(T{10});
			VERIFY(&r0 == &v[1]);
			VERIFY(&r1 == &v[2]);
			VERIFY(&r2 == &v[3]);
			VERIFY(&r3 == &v[0]);
		}
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			auto& r4 = v.emplace_front(T{11});
			VERIFY(&r0 == &v[1]);
			VERIFY(&r1 == &v[2]);
			VERIFY(&r2 == &v[3]);
			VERIFY(&r3 == &v[4]);
			VERIFY(&r4 == &v[0]);
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 1);
		VERIFY(v[3] == 2);
		VERIFY(v[4] == 3);

		{
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			auto& r4 = v[4];
			auto& r5 = v.emplace_front(T{12});
			VERIFY(&r0 == &v[1]);
			VERIFY(&r1 == &v[2]);
			VERIFY(&r2 == &v[3]);
			VERIFY(&r3 == &v[4]);
			VERIFY(&r4 == &v[5]);
			VERIFY(&r5 == &v[0]);
		}
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 12);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 1);
		VERIFY(v[4] == 2);
		VERIFY(v[5] == 3);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::deque<MoveOnly> v;

		auto& r1 = v.emplace_front(10);
		VERIFY(&r1 == &v[0]);
		VERIFY(v.size() == 1);
		VERIFY(v[0].value == 10);

		auto& r2 = v.emplace_front(11);
		VERIFY(&r2 == &v[0]);
		VERIFY(v.size() == 2);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 10);

		auto& r3 = v.emplace_front(12);
		VERIFY(&r3 == &v[0]);
		VERIFY(v.size() == 3);
		VERIFY(v[0].value == 12);
		VERIFY(v[1].value == 11);
		VERIFY(v[2].value == 10);
	}
	{
		hamon::deque<S> v;

		auto& r1 = v.emplace_front(10);
		VERIFY(&r1 == &v[0]);
		VERIFY(v.size() == 1);
		VERIFY(v[0].value == 10);

		auto& r2 = v.emplace_front(11, 12);
		VERIFY(&r2 == &v[0]);
		VERIFY(v.size() == 2);
		VERIFY(v[0].value == 23);
		VERIFY(v[1].value == 10);

		auto& r3 = v.emplace_front(1, 2, 3);
		VERIFY(&r3 == &v[0]);
		VERIFY(v.size() == 3);
		VERIFY(v[0].value == 6);
		VERIFY(v[1].value == 23);
		VERIFY(v[2].value == 10);
	}

	return true;
}

#undef VERIFY

#if !defined(HAMON_NO_EXCEPTIONS)
struct MayThrow
{
	struct Exception{};

	int value;

	MayThrow(int v) : value(v)
	{
		if (v < 0)
		{
			throw Exception{};
		}
	}
};

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

GTEST_TEST(DequeTest, EmplaceFrontTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::deque<MayThrow> v;

		v.emplace_front(2);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);

		EXPECT_THROW(v.emplace_front(-2), MayThrow::Exception);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<MayThrow> v;

		EXPECT_THROW(v.emplace_front(-1), MayThrow::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_front(3);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 3, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v;

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_front(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v(2);

		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.emplace_front(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ( 2, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ(13, v[2].value);
	}
	{
		hamon::deque<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.emplace_front(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ(14, v[3].value);

		EXPECT_THROW(v.emplace_front(ThrowOnMove(2)), ThrowOnMove::Exception);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ(14, v[3].value);
	}
#endif
}

}	// namespace emplace_front_test

}	// namespace hamon_deque_test
