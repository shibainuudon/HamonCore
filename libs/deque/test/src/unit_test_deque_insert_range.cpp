/**
 *	@file	unit_test_deque_insert_range.cpp
 *
 *	@brief	insert_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	iterator insert_range(const_iterator position, R&& rg);
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

namespace insert_range_test
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
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;
	using Range = RangeWrapper<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range const&>())),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range&&>())),
		Iterator
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range const&>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque&>().insert_range(hamon::declval<ConstIterator>(), hamon::declval<Range&&>())), "");

	{
		Deque v{1,2,3};

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
		Deque v{1,2,3,4};

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
		Deque v{1,2};

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

	// 関数呼び出し後、イテレータは無効化されるが参照は無効化されない
	{
		Deque v{1,2,3,4};

		{
			T a[] = {10,20,30,40,50};
			Range rng(a);
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.insert_range(v.begin(), rng);
			VERIFY(ValidReference(r0, v));
			VERIFY(ValidReference(r1, v));
			VERIFY(ValidReference(r2, v));
			VERIFY(ValidReference(r3, v));
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 10);
		VERIFY(v[1] == 20);
		VERIFY(v[2] == 30);
		VERIFY(v[3] == 40);
		VERIFY(v[4] == 50);
		VERIFY(v[5] == 1);
		VERIFY(v[6] == 2);
		VERIFY(v[7] == 3);
		VERIFY(v[8] == 4);
	}
	{
		Deque v{1,2,3,4};

		{
			T a[] = {10,20,30,40,50};
			Range rng(a);
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.insert_range(v.begin() + 1, rng);
			VERIFY(ValidReference(r0, v));
			VERIFY(ValidReference(r1, v));
			VERIFY(ValidReference(r2, v));
			VERIFY(ValidReference(r3, v));
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 10);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 30);
		VERIFY(v[4] == 40);
		VERIFY(v[5] == 50);
		VERIFY(v[6] == 2);
		VERIFY(v[7] == 3);
		VERIFY(v[8] == 4);
	}
	{
		Deque v{1,2,3,4};

		{
			T a[] = {10,20,30,40,50};
			Range rng(a);
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.insert_range(v.begin() + 2, rng);
			VERIFY(ValidReference(r0, v));
			VERIFY(ValidReference(r1, v));
			VERIFY(ValidReference(r2, v));
			VERIFY(ValidReference(r3, v));
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 10);
		VERIFY(v[3] == 20);
		VERIFY(v[4] == 30);
		VERIFY(v[5] == 40);
		VERIFY(v[6] == 50);
		VERIFY(v[7] == 3);
		VERIFY(v[8] == 4);
	}
	{
		Deque v{1,2,3,4};

		{
			T a[] = {10,20,30,40,50};
			Range rng(a);
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.insert_range(v.begin() + 3, rng);
			VERIFY(ValidReference(r0, v));
			VERIFY(ValidReference(r1, v));
			VERIFY(ValidReference(r2, v));
			VERIFY(ValidReference(r3, v));
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 20);
		VERIFY(v[5] == 30);
		VERIFY(v[6] == 40);
		VERIFY(v[7] == 50);
		VERIFY(v[8] == 4);
	}
	{
		Deque v{1,2,3,4};

		{
			T a[] = {10,20,30,40,50};
			Range rng(a);
			auto& r0 = v[0];
			auto& r1 = v[1];
			auto& r2 = v[2];
			auto& r3 = v[3];
			v.insert_range(v.begin() + 4, rng);
			VERIFY(ValidReference(r0, v));
			VERIFY(ValidReference(r1, v));
			VERIFY(ValidReference(r2, v));
			VERIFY(ValidReference(r3, v));
		}
		VERIFY(v.size() == 9);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);
		VERIFY(v[4] == 10);
		VERIFY(v[5] == 20);
		VERIFY(v[6] == 30);
		VERIFY(v[7] == 40);
		VERIFY(v[8] == 50);
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

GTEST_TEST(DequeTest, InsertRangeTest)
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

		EXPECT_THROW(v2.insert_range(v2.end(), v1), ThrowOnCopy::Exception);
		EXPECT_EQ(2u, v2.size());
		EXPECT_EQ(13, v2[0].value);
		EXPECT_EQ(13, v2[1].value);
	}
#endif
}

}	// namespace insert_range_test

}	// namespace hamon_deque_test
