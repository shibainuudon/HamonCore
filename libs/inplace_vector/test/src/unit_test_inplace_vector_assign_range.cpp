/**
 *	@file	unit_test_inplace_vector_assign_range.cpp
 *
 *	@brief	assign_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr void assign_range(R&& rg);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_inplace_vector_test
{

namespace assign_range_test
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

	ThrowOnCopy& operator=(ThrowOnCopy &&) = default;
};
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Range = RangeWrapper<T>;

	{
		InplaceVector v;
		Range r;
		static_assert(hamon::is_same<decltype(v.assign_range(r)), void>::value, "");
		static_assert(!noexcept(v.assign_range(r)), "");
	}
	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T a[] = {T{1}, T{2}, T{3}};
		v.assign_range(Range(a, a));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_5()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Range = RangeWrapper<T>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		{
			T a[] = {T{1}, T{2}, T{3}};
			v.assign_range(Range{a});
		}
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});

		{
			T a[] = {T{4}, T{5}};
			v.assign_range(Range{a});
		}
		VERIFY(v.size() == 2);
		VERIFY(v[0] == T{4});
		VERIFY(v[1] == T{5});

		{
			T a[] = {T{10}, T{11}, T{12}, T{13}, T{14}};
			v.assign_range(Range{a});
		}
		VERIFY(v.size() == 5);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{11});
		VERIFY(v[2] == T{12});
		VERIFY(v[3] == T{13});
		VERIFY(v[4] == T{14});
	}
	return true;
}

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	VERIFY((test_impl_0<T, 0, RangeWrapper>()));
	VERIFY((test_impl_0<T, 1, RangeWrapper>()));
	VERIFY((test_impl_0<T, 2, RangeWrapper>()));
	VERIFY((test_impl_0<T, 5, RangeWrapper>()));
	VERIFY((test_impl_0<T, 6, RangeWrapper>()));

//	VERIFY((test_impl_5<T, 0, RangeWrapper>()));
//	VERIFY((test_impl_5<T, 1, RangeWrapper>()));
//	VERIFY((test_impl_5<T, 2, RangeWrapper>()));
	VERIFY((test_impl_5<T, 5, RangeWrapper>()));
	VERIFY((test_impl_5<T, 6, RangeWrapper>()));

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

GTEST_TEST(InplaceVectorTest, AssignRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		int const a[]{1,2,3};
		hamon::inplace_vector<int, 0> v;
		EXPECT_THROW(v.assign_range(a), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 3> v;
		{
			int const a[]{1,2,3};
			EXPECT_NO_THROW(v.assign_range(a));
		}
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		{
			int const a[]{4,5,6,7};
			EXPECT_THROW(v.assign_range(a), hamon::bad_alloc);
		}
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		v.emplace_back(10);
		v.emplace_back(20);
		{
			ThrowOnCopy const a[]{1};
			EXPECT_THROW(v.assign_range(a), ThrowOnCopy::Exception);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		{
			ThrowOnCopy const a[]{1,2};
			EXPECT_THROW(v.assign_range(a), ThrowOnCopy::Exception);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		{
			ThrowOnCopy const a[]{1,2,3};
			EXPECT_THROW(v.assign_range(a), ThrowOnCopy::Exception);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		{
			ThrowOnCopy const a[]{1,2,3,4};
			EXPECT_THROW(v.assign_range(a), hamon::bad_alloc);
		}
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/assign_range
	{
		const auto source = {1, 2, 3};
		hamon::inplace_vector<int, 4> destination {4, 5};
		destination.assign_range(source);
		EXPECT_TRUE(hamon::ranges::equal(destination, source));

#if !defined(HAMON_NO_EXCEPTIONS)
		{
			const auto bad = {-1, -2, -3, -4, -5};
			EXPECT_THROW(destination.assign_range(bad), hamon::bad_alloc); // throws: bad.size() > destination.capacity()
		}
#endif
	}
}

}	// namespace assign_range_test

}	// namespace hamon_inplace_vector_test
