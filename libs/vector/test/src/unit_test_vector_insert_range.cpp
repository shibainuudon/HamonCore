/**
 *	@file	unit_test_vector_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr iterator insert_range(const_iterator position, R&& rg);
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_vector_test
{

namespace insert_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = std::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;
	using Iterator = typename Vector::iterator;
	using ConstIterator = typename Vector::const_iterator;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range const&>())),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range&&>())),
		Iterator
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range&&>())), "");

	{
		Vector v{1,2,3};

		T a[] = {11,12,13,14};
		Range r(a);

		auto ret = v.insert_range(v.begin(), r);
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 14);
		VERIFY(v[4] == 1);
		VERIFY(v[5] == 2);
		VERIFY(v[6] == 3);
	}
	{
		Vector v{1,2,3,4};

		T a[] = {10,20};
		Range r(a);

		auto ret = v.insert_range(v.begin() + 1, r);
		VERIFY(ret == v.begin() + 1);
		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 2);
		VERIFY(v[4] == 3);
		VERIFY(v[5] == 4);
	}
	{
		Vector v{1,2};

		T a[] = {10,20,30};
		Range r(a);

		auto ret = v.insert_range(v.end(), r);
		VERIFY(ret == v.begin() + 2);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 30);
	}
	{
		Vector v{1,2,3};
		T a[] = {10,20};
		Range r(a);
		v.reserve(5);
		// メモリの再確保が行われないときは、挿入位置より前のイテレータは無効にならない
		auto it1 = v.begin();
		auto it2 = v.begin() + 1;
		auto ret = v.insert_range(v.begin() + 2, r);
		VERIFY(ret == v.begin() + 2);
		VERIFY(it1 == v.begin());
		VERIFY(it2 == v.begin() + 1);
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 3);
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

	ThrowOnCopy& operator=(ThrowOnCopy const&)
	{
		throw Exception{};
	}
};
#endif

GTEST_TEST(VectorTest, InsertRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_input_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_forward_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_bidirectional_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_random_access_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_contiguous_range>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_input_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_forward_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_bidirectional_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_random_access_sized_range>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<test_contiguous_sized_range>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::vector<ThrowOnCopy> v1(3);
		hamon::vector<ThrowOnCopy> v2(2);

		auto const old_capacity = v2.capacity();
		auto const old_data = v2.data();
		EXPECT_THROW(v2.insert_range(v2.end(), v1), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v2.capacity());
		EXPECT_EQ(old_data, v2.data());
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
#endif
}

}	// namespace insert_range_test

}	// namespace hamon_vector_test
