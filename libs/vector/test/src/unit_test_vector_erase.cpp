/**
 *	@file	unit_test_vector_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator erase(const_iterator position);
 *	constexpr iterator erase(const_iterator first, const_iterator last);
 *
 *	template<class T, class Allocator, class U = T>
 *	constexpr typename vector<T, Allocator>::size_type
 *	erase(vector<T, Allocator>& c, const U& value);
 */

#include <hamon/vector.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().erase(hamon::declval<ConstIterator>())),
		Iterator
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Vector&>().erase(hamon::declval<ConstIterator>())), "");
#endif

	{
		Vector v {1,2,3,4,5};
		auto const old_capacity = v.capacity();
		auto ret = v.erase(v.begin());
		VERIFY(ret == v.begin());
		VERIFY(v.capacity() == old_capacity);	// capacityは変化しない
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 2);
		VERIFY(v[1] == 3);
		VERIFY(v[2] == 4);
		VERIFY(v[3] == 5);
	}
	{
		Vector v {1,2,3,4,5};
		// 削除位置より前のイテレータは無効にならない
		auto const it1 = v.begin();
		auto const it2 = v.begin() + 1;
		auto const old_capacity = v.capacity();
		auto ret = v.erase(v.begin() + 2);
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.capacity() == old_capacity);	// capacityは変化しない
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 4);
		VERIFY(v[3] == 5);
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())),
		Iterator
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Vector&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");
#endif

	{
		Vector v {1,2,3,4,5};
		// 削除位置より前のイテレータは無効にならない
		auto const it = v.begin();
		auto const old_capacity = v.capacity();
		auto ret = v.erase(v.begin() + 1, v.begin() + 3);
		VERIFY(it == v.begin());
		VERIFY(ret == v.begin() + 1);
		VERIFY(v.capacity() == old_capacity);	// capacityは変化しない
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 4);
		VERIFY(v[2] == 5);
	}
	{
		Vector v {1,2,3,4,5};
		auto const old_capacity = v.capacity();
		auto ret = v.erase(v.begin(), v.end());
		VERIFY(ret == v.begin());
		VERIFY(v.capacity() == old_capacity);	// capacityは変化しない
		VERIFY(v.size() == 0);
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	using T = int;
	using Vector = hamon::vector<T>;
	using SizeType = typename Vector::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::erase(hamon::declval<Vector&>(), hamon::declval<T const&>())),
		SizeType
	>::value, "");

	static_assert(!noexcept(
		hamon::erase(hamon::declval<Vector&>(), hamon::declval<T const&>())), "");

	{
		Vector v = {3,1,4,5,2};
		auto r = hamon::erase(v, 1);
		VERIFY(r == 1);
		const T v2[] = {3,4,5,2,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		Vector v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9,};
		auto r = hamon::erase(v, 9);
		VERIFY(r == 10);
		const T v2[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, EraseTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());
}

}	// namespace erase_test

}	// namespace hamon_vector_test
