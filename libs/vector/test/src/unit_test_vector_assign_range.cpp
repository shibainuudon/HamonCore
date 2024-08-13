/**
 *	@file	unit_test_vector_assign_range.cpp
 *
 *	@brief	assign_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr void assign_range(R&& rg);
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

namespace assign_range_test
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
		decltype(hamon::declval<Vector>().assign_range(hamon::declval<Range&&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector>().assign_range(hamon::declval<Range const&>())),
		void
	>::value, "");
	static_assert(!noexcept(
		hamon::declval<Vector>().assign_range(hamon::declval<Range&&>())), "");
	static_assert(!noexcept(
		hamon::declval<Vector>().assign_range(hamon::declval<Range const&>())), "");

	Vector v;

	{
		T a[] = {1,2,3,4};
		v.assign_range(Range{a});
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
	}
	{
		T a[] = {11,12};
		Range r(a);
		v.assign_range(r);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
	}
	{
		T a[] = {21,22};
		Range const r(a);
		v.assign_range(r);
		VERIFY(v.size() == 2);
		VERIFY(v[0] == 21);
		VERIFY(v[1] == 22);
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

GTEST_TEST(VectorTest, AssignRangeTest)
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
		hamon::vector<ThrowOnCopy> v;
		ThrowOnCopy a[] = {ThrowOnCopy{1}, ThrowOnCopy{2}, ThrowOnCopy{3}};
		test_input_range<ThrowOnCopy> r(a);

		EXPECT_THROW(v.assign_range(r), ThrowOnCopy::Exception);
		EXPECT_EQ(0u, v.size());

		v.emplace_back(10);
		{
			auto const old_capacity = v.capacity();
			auto const old_data = v.data();
			EXPECT_THROW(v.assign_range(r), ThrowOnCopy::Exception);
			EXPECT_EQ(old_capacity, v.capacity());
			EXPECT_EQ(old_data, v.data());
		}
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(10, v[0].value);

		v.emplace_back(11);
		v.emplace_back(12);
		v.emplace_back(13);
		v.emplace_back(14);
		{
			auto const old_capacity = v.capacity();
			auto const old_data = v.data();
			EXPECT_THROW(v.assign_range(r), ThrowOnCopy::Exception);
			EXPECT_EQ(old_capacity, v.capacity());
			EXPECT_EQ(old_data, v.data());
		}
		EXPECT_EQ(5u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(11, v[1].value);
		EXPECT_EQ(12, v[2].value);
		EXPECT_EQ(13, v[3].value);
		EXPECT_EQ(14, v[4].value);
	}
#endif
}

}	// namespace assign_range_test

}	// namespace hamon_vector_test
