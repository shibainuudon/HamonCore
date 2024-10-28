/**
 *	@file	unit_test_inplace_vector_try_append_range.cpp
 *
 *	@brief	try_append_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr ranges::borrowed_iterator_t<R> try_append_range(R&& rg);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/iterator.hpp>
#include <hamon/ranges.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_inplace_vector_test
{

namespace try_append_range_test
{

struct S1
{
	int m_value;
	constexpr bool operator==(S1 const& y) const { return m_value == y.m_value; }
};

struct S2
{
	int m_value;
	S2() = default;
	constexpr S2(int v) : m_value(v) {}
	constexpr S2(S2 const& x) : m_value(x.m_value) {}
	S2& operator=(S2 const&) = default;
	S2& operator=(S2 &&) = default;
	constexpr bool operator==(S2 const& y) const { return m_value == y.m_value; }
};

struct S3
{
	int m_value;
	constexpr S3() : m_value(0) {}
	constexpr S3(int v) : m_value(v) {}
	constexpr S3(S3 const& x) : m_value(x.m_value) {}
	S3& operator=(S3 const&) = default;
	S3& operator=(S3 &&) = default;
	constexpr bool operator==(S3 const& y) const { return m_value == y.m_value; }
};

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	struct Exception{};

	int value;

	ThrowOnCopy(int v) : value(v)
	{
	}

	ThrowOnCopy(ThrowOnCopy const& other)
		: value(other.value)
	{
		if (value < 0)
		{
			throw Exception{};
		}
	}

	ThrowOnCopy(ThrowOnCopy&& other) noexcept
		: value(other.value)
	{
	}
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	using Range = RangeWrapper<T>;

	{
		hamon::inplace_vector<T, 10> v;
		Range r;
		static_assert(hamon::is_same<decltype(v.try_append_range(r)), hamon::ranges::iterator_t<Range>>::value, "");
		static_assert(hamon::is_same<decltype(v.try_append_range(Range{})), hamon::ranges::dangling>::value, "");
		static_assert(!noexcept(v.try_append_range(r)), "");
		static_assert(!noexcept(v.try_append_range(Range{})), "");
	}
	{
		hamon::inplace_vector<T, 0> v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			T a[] = {T{1}, T{2}, T{3}};
			Range r(a, a);
			auto it = v.try_append_range(r);
			VERIFY(it == r.begin());
			VERIFY(it == r.end());
		}
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			T a[] = {T{1}, T{2}, T{3}};
			Range r(a);
			auto it = v.try_append_range(r);
			VERIFY(it == r.begin());
			VERIFY(it != r.end());
		}
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}
	{
		hamon::inplace_vector<T, 4> v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			T a[] = {T{1}, T{2}, T{3}};
			Range r(a);
			auto it = v.try_append_range(r);
			VERIFY(it != r.begin());
			VERIFY(it == r.end());
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});

		{
			T a[] = {T{4}, T{5}, T{6}};
			Range r(a);
			auto it = v.try_append_range(r);
			VERIFY(it != r.begin());
			VERIFY(it == hamon::next(r.begin(), 1));
			VERIFY(it != r.end());
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
		VERIFY(v[3] == T{4});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl<T, test_input_range>()));
	VERIFY((test_impl<T, test_forward_range>()));
	VERIFY((test_impl<T, test_bidirectional_range>()));
	VERIFY((test_impl<T, test_random_access_range>()));
	VERIFY((test_impl<T, test_contiguous_range>()));

	VERIFY((test_impl<T, test_input_sized_range>()));
	VERIFY((test_impl<T, test_forward_sized_range>()));
	VERIFY((test_impl<T, test_bidirectional_sized_range>()));
	VERIFY((test_impl<T, test_random_access_sized_range>()));
	VERIFY((test_impl<T, test_contiguous_sized_range>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, TryAppendRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::inplace_vector<ThrowOnCopy, 5> v;
		v.emplace_back(1);
		{
			ThrowOnCopy const a[] { {10}, {-11}, {12}, {13} };
			EXPECT_THROW(v.try_append_range(a), ThrowOnCopy::Exception);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(10, v[1].value);
		{
			ThrowOnCopy const a[] { {20}, {21}, {-22} };
			EXPECT_THROW(v.try_append_range(a), ThrowOnCopy::Exception);
		}
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_EQ(20, v[2].value);
		EXPECT_EQ(21, v[3].value);
		{
			ThrowOnCopy const a[] { {30}, {-31} };
			EXPECT_NO_THROW(v.try_append_range(a));
		}
		EXPECT_EQ(5u, v.size());
		EXPECT_EQ( 1, v[0].value);
		EXPECT_EQ(10, v[1].value);
		EXPECT_EQ(20, v[2].value);
		EXPECT_EQ(21, v[3].value);
		EXPECT_EQ(30, v[4].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/try_append_range
	{
		using I = hamon::inplace_vector<int, 8>;
		auto nums = I {1, 2, 3};
		const auto rg = {-1, -2, -3};

		auto it = nums.try_append_range(rg);
		EXPECT_TRUE(nums.size() == 6);
		EXPECT_TRUE((nums == I {1, 2, 3, -1, -2, -3}));
		EXPECT_TRUE(it == rg.end());

		it = nums.try_append_range(rg);
		EXPECT_TRUE(nums.size() == 8);
		EXPECT_TRUE((nums == I {1, 2, 3, -1, -2, -3, -1, -2}));
		EXPECT_TRUE(it == rg.begin() + 2);
	}
}

}	// namespace try_append_range_test

}	// namespace hamon_inplace_vector_test
