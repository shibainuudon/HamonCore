/**
 *	@file	unit_test_vector_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace(const_iterator position, Args&&... args);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace emplace_test
{

struct MoveOnly
{
	int value;
	HAMON_CXX11_CONSTEXPR MoveOnly(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly const& x) : value(x.value) {} //= delete;	// TODO Visual Studio 2019 だけ？
	HAMON_CXX11_CONSTEXPR MoveOnly(MoveOnly && x) noexcept : value(x.value) {}
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly const&) = delete;
	HAMON_CXX14_CONSTEXPR MoveOnly& operator=(MoveOnly && x) noexcept { value = x.value; return *this; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().emplace(hamon::declval<ConstIterator>())),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().emplace(hamon::declval<ConstIterator>(), hamon::declval<T>())),
		Iterator
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().emplace(hamon::declval<ConstIterator>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().emplace(hamon::declval<ConstIterator>(), hamon::declval<T>())), "");

	{

		Vector v;
		v.emplace(v.begin(), 10);
		VERIFY(v.size() == 1);
		VERIFY(v[0] == 10);

		v.emplace(v.begin(), 20);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 10);

		v.emplace(v.end(), 30);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 20);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 30);
	}
	{

		Vector v;
		v.emplace(v.begin(), 10);

		v.reserve(3);

		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		{
			auto const it = v.begin();
			v.emplace(v.end(), 20);
			VERIFY(it == v.begin());
			VERIFY(v.size() == 2);
			VERIFY(v[0] == 10);
			VERIFY(v[1] == 20);
		}
		{
			auto const it = v.begin();
			v.emplace(v.begin() + 1, 30);
			VERIFY(it == v.begin());
			VERIFY(v.size() == 3);
			VERIFY(v[0] == 10);
			VERIFY(v[1] == 30);
			VERIFY(v[2] == 20);
		}
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::vector<MoveOnly> v;

		auto r1 = v.emplace(v.begin(), 10);
		VERIFY(r1 == v.begin());
		VERIFY(v.size() == 1);
		VERIFY(v[0].value == 10);

		auto r2 = v.emplace(v.begin(), 11);
		VERIFY(r2 == v.begin());
		VERIFY(v.size() == 2);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 10);

		auto r3 = v.emplace(v.begin() + 1, 12);
		VERIFY(r3 == v.begin() + 1);
		VERIFY(v.size() == 3);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 12);
		VERIFY(v[2].value == 10);

		auto r4 = v.emplace(v.end(), 13);
		VERIFY(r4 == v.begin() + 3);
		VERIFY(v.size() == 4);
		VERIFY(v[0].value == 11);
		VERIFY(v[1].value == 12);
		VERIFY(v[2].value == 10);
		VERIFY(v[3].value == 13);
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
#endif

GTEST_TEST(VectorTest, EmplaceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<MayThrow> v;

		v.emplace(v.end(), 2);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);

		auto const old_capacity = v.capacity();
		auto const old_data = v.data();
		EXPECT_THROW(v.emplace(v.end(), -2), MayThrow::Exception);
		EXPECT_EQ(old_capacity, v.capacity());
		EXPECT_EQ(old_data, v.data());
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ( 2, v[0].value);
	}
#endif
}

}	// namespace emplace_test

}	// namespace hamon_vector_test
