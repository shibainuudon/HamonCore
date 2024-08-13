/**
 *	@file	unit_test_vector_append_range.cpp
 *
 *	@brief	append_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr void append_range(R&& rg);
 */

#include <hamon/vector.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_vector_test
{

namespace append_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = hamon::allocator<T>;
	using Vector = hamon::vector<T, Allocator>;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().append_range(hamon::declval<Range const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().append_range(hamon::declval<Range&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Vector&>().append_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector&>().append_range(hamon::declval<Range&&>())), "");

	{
		Vector v{1,2,3};

		T a[] = {11,12,13,14};
		Range r(a);

		v.append_range(r);
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 11);
		VERIFY(v[4] == 12);
		VERIFY(v[5] == 13);
		VERIFY(v[6] == 14);
	}
	{
		Vector v;
		v.push_back(1);
		v.reserve(5);

		// メモリの再確保が行われないときは、end()以外のイテレータは無効にならない
		auto const it = v.begin();

		T a[] = {11,12,13,14};
		Range r(a);

		v.append_range(r);
		VERIFY(it == v.begin());
		VERIFY(v.size() == 5);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 14);
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

GTEST_TEST(VectorTest, AppendRangeTest)
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
		EXPECT_THROW(v2.append_range(v1), ThrowOnCopy::Exception);
		EXPECT_EQ(old_capacity, v2.capacity());
		EXPECT_EQ(old_data, v2.data());
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
#endif
}

}	// namespace append_range_test

}	// namespace hamon_vector_test
