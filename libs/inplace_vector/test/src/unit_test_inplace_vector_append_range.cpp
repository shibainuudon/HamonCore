/**
 *	@file	unit_test_inplace_vector_append_range.cpp
 *
 *	@brief	append_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	constexpr void append_range(R&& rg);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_inplace_vector_test
{

namespace append_range_test
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
};

struct ThrowOnMove
{
	struct Exception{};

	int value;

	ThrowOnMove(int v) : value(v)
	{
	}

	ThrowOnMove(ThrowOnMove const& other)
		: value(other.value)
	{
	}

	ThrowOnMove(ThrowOnMove&&)
	{
		throw Exception{};
	}
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
		static_assert(hamon::is_same<decltype(v.append_range(hamon::declval<Range>())), void>::value, "");
		static_assert(!noexcept(v.append_range(hamon::declval<Range>())), "");
	}

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T a[] = {T{1}, T{2}, T{3}};
		Range r(a, a);
		v.append_range(r);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename T, hamon::size_t N, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;
	using Range = RangeWrapper<T>;

	{
		InplaceVector v;
		VERIFY(v.empty());
		VERIFY(v.size() == 0);

		T a[] = {T{1}, T{2}, T{3}};
		Range r(a);
		v.append_range(r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{1});
		VERIFY(v[1] == T{2});
		VERIFY(v[2] == T{3});
	}
	{
		InplaceVector v(1, T{10});
		VERIFY(!v.empty());
		VERIFY(v.size() == 1);
		VERIFY(v[0] == T{10});

		T a[] = {T{20}, T{30}};
		Range r(a);
		v.append_range(r);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[0] == T{10});
		VERIFY(v[1] == T{20});
		VERIFY(v[2] == T{30});
	}

	return true;
}

template <typename T, template <typename> class RangeWrapper>
HAMON_CXX14_CONSTEXPR bool test_impl()
{
	VERIFY((test_impl_0<T, 0, RangeWrapper>()));
	VERIFY((test_impl_0<T, 1, RangeWrapper>()));
	VERIFY((test_impl_0<T, 2, RangeWrapper>()));
	VERIFY((test_impl_0<T, 3, RangeWrapper>()));
	VERIFY((test_impl_0<T, 4, RangeWrapper>()));

//	VERIFY((test_impl_3<T, 0, RangeWrapper>()));
//	VERIFY((test_impl_3<T, 1, RangeWrapper>()));
//	VERIFY((test_impl_3<T, 2, RangeWrapper>()));
	VERIFY((test_impl_3<T, 3, RangeWrapper>()));
	VERIFY((test_impl_3<T, 4, RangeWrapper>()));

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

GTEST_TEST(InplaceVectorTest, AppendRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::inplace_vector<int, 0> v;
		int a[3]{};
		EXPECT_THROW(v.append_range(a), hamon::bad_alloc);
		EXPECT_TRUE(v.empty());
		EXPECT_EQ(0u, v.size());
	}
	{
		hamon::inplace_vector<int, 3> v;
		int a[]{1,2};
		EXPECT_NO_THROW(v.append_range(a));
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_THROW(v.append_range(a), hamon::bad_alloc);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		int b[]{3};
		EXPECT_NO_THROW(v.append_range(b));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_THROW(v.append_range(b), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
	}
	{
		hamon::inplace_vector<ThrowOnCopy, 3> v;
		ThrowOnCopy const a[] { {10}, {20}, {30} };
		EXPECT_THROW(v.append_range(a), ThrowOnCopy::Exception);
		EXPECT_TRUE(v.empty());
		v.emplace_back(1);
		EXPECT_EQ(1u, v.size());
		EXPECT_EQ(1, v[0].value);
		EXPECT_THROW(v.append_range(a), hamon::bad_alloc);
	}
	{
		hamon::inplace_vector<ThrowOnMove, 3> v;
		ThrowOnMove const a[] { {10}, {20}, {30} };
		EXPECT_NO_THROW(v.append_range(a));
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(30, v[2].value);
		EXPECT_THROW(v.append_range(a), hamon::bad_alloc);
		EXPECT_EQ(3u, v.size());
		EXPECT_EQ(10, v[0].value);
		EXPECT_EQ(20, v[1].value);
		EXPECT_EQ(30, v[2].value);
	}
#endif

	// https://en.cppreference.com/w/cpp/container/inplace_vector/append_range
	{
		using I = hamon::inplace_vector<int, 8>;
		auto head = I {1, 2, 3, 4};
		const auto tail = {-5, -6, -7};
		head.append_range(tail);
		EXPECT_TRUE(head.size() == 7);
		EXPECT_TRUE((head == I {1, 2, 3, 4, -5, -6, -7}));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW(head.append_range(tail), hamon::bad_alloc); // throws: no space
#endif
	}
}

}	// namespace append_range_test

}	// namespace hamon_inplace_vector_test
