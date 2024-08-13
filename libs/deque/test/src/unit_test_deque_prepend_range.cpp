/**
 *	@file	unit_test_deque_prepend_range.cpp
 *
 *	@brief	prepend_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	void prepend_range(R&& rg);
 */

#include <hamon/deque.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_deque_test
{

namespace prepend_range_test
{

template <typename T, typename Deque>
HAMON_CXX20_CONSTEXPR bool ValidReference(T const& t, Deque const& d)
{
	for (auto& x : d)
	{
		if (t == x)
		{
			return true;
		}
	}
	return false;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = hamon::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().prepend_range(hamon::declval<Range const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().prepend_range(hamon::declval<Range&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().prepend_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().prepend_range(hamon::declval<Range&&>())), "");

	{
		Deque v{1,2,3};

		T a[] = {11,12,13,14};
		Range r(a);

		v.prepend_range(r);
		VERIFY(v.size() == 7);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 14);
		VERIFY(v[4] == 1);
		VERIFY(v[5] == 2);
		VERIFY(v[6] == 3);
	}

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1};

		{
			T a[] = {11,12,13};
			Range rng(a);
			auto& r0 = v[0];
			v.prepend_range(rng);
			VERIFY(ValidReference(r0, v));
		}

		VERIFY(v.size() == 4);
		VERIFY(v[0] == 11);
		VERIFY(v[1] == 12);
		VERIFY(v[2] == 13);
		VERIFY(v[3] == 1);

		{
			T a[] = {21,22,23,24};
			Range rng(a);
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.prepend_range(rng);
			VERIFY(ValidReference(r0, v));
			VERIFY(ValidReference(r1, v));
			VERIFY(ValidReference(r2, v));
			VERIFY(ValidReference(r3, v));
		}

		VERIFY(v.size() == 8);
		VERIFY(v[0] == 21);
		VERIFY(v[1] == 22);
		VERIFY(v[2] == 23);
		VERIFY(v[3] == 24);
		VERIFY(v[4] == 11);
		VERIFY(v[5] == 12);
		VERIFY(v[6] == 13);
		VERIFY(v[7] == 1);

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

GTEST_TEST(DequeTest, PrependRangeTest)
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
	// 操作中に例外が発生した場合、副作用は発生しない
	{
		hamon::deque<ThrowOnCopy> v1(3);
		hamon::deque<ThrowOnCopy> v2(2);

		EXPECT_THROW(v2.prepend_range(v1), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
#endif
}

}	// namespace prepend_range_test

}	// namespace hamon_deque_test
