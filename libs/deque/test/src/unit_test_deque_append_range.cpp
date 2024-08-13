/**
 *	@file	unit_test_deque_append_range.cpp
 *
 *	@brief	append_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	void append_range(R&& rg);
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

namespace append_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class RangeWrapper>
HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Allocator = hamon::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().append_range(hamon::declval<Range const&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().append_range(hamon::declval<Range&&>())),
		void
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().append_range(hamon::declval<Range const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().append_range(hamon::declval<Range&&>())), "");

	{
		Deque v{1,2,3};

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

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v;
		v.push_back(1);

		auto& r0 = v[0];

		{
			T a[] = {11,12,13};
			Range r(a);
			v.append_range(r);
		}

		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);

		VERIFY(&r0 == &v[0]);

		auto& r1 = v[1];
		auto& r2 = v[2];
		auto& r3 = v[3];

		{
			T a[] = {21,22};
			Range r(a);
			v.append_range(r);
		}

		VERIFY(v.size() == 6);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 11);
		VERIFY(v[2] == 12);
		VERIFY(v[3] == 13);
		VERIFY(v[4] == 21);
		VERIFY(v[5] == 22);

		VERIFY(&r0 == &v[0]);
		VERIFY(&r1 == &v[1]);
		VERIFY(&r2 == &v[2]);
		VERIFY(&r3 == &v[3]);
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

GTEST_TEST(DequeTest, AppendRangeTest)
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

		EXPECT_THROW(v2.append_range(v1), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
#endif
}

}	// namespace append_range_test

}	// namespace hamon_deque_test
