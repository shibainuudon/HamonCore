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

#if 0
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

/*HAMON_CXX20_CONSTEXPR*/ bool test1()
{
	using T = int;
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
		auto& r = v.emplace_front(10);
		VERIFY(&r == &v[0]);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 1);
		VERIFY(v[2] == 2);
		VERIFY(v[3] == 3);
	}
#if 0
	{
		Deque v{1,2,3};
		v.reserve(4);
		// メモリの再確保が行われないときは、end()以外のイテレータは無効にならない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto const it3 = v.begin() + 2;
		v.emplace_front(10);
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

/*HAMON_CXX20_CONSTEXPR*/ bool test2()
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
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test1());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::deque<MayThrow> v;

		v.emplace_front(2);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		EXPECT_THROW(v.emplace_front(-2), MayThrow::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<MayThrow> v;

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		EXPECT_THROW(v.emplace_front(-1), MayThrow::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.emplace_front(3);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 3, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v;

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(0u, v.size());

		v.emplace_front(ThrowOnCopy(2));
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
	{
		hamon::deque<ThrowOnCopy> v(2);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.emplace_front(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ( 2, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ(13, v[2].value);
	}
#if 0
	{
		hamon::deque<ThrowOnCopy> v(2);
		v.reserve(10);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		ThrowOnCopy const t(1);
		EXPECT_THROW(v.emplace_front(t), ThrowOnCopy::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);

		v.emplace_front(ThrowOnCopy(2));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(13, v[0].value);
		EXPECT_EQ(13, v[1].value);
		EXPECT_EQ( 2, v[2].value);
	}
#endif
	{
		hamon::deque<ThrowOnMove> v(3);

		ThrowOnMove const t(1);
		v.emplace_front(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ(14, v[3].value);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		EXPECT_THROW(v.emplace_front(ThrowOnMove(2)), ThrowOnMove::Exception);
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
		v.emplace_front(t);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);

		//auto const old_capacity = v.capacity();
		//auto const old_data = v.data();
		EXPECT_THROW(v.emplace_front(ThrowOnMove(2)), ThrowOnMove::Exception);
		//EXPECT_EQ(old_capacity, v.capacity());
		//EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(14, v[0].value);
		EXPECT_EQ(14, v[1].value);
		EXPECT_EQ(14, v[2].value);
		EXPECT_EQ( 1, v[3].value);
	}
#endif
#endif
}

}	// namespace emplace_front_test

}	// namespace hamon_deque_test
#endif
