/**
 *	@file	unit_test_inplace_vector_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(inplace_vector& x)
 *	noexcept(N == 0 || (is_nothrow_swappable_v<T> &&
 *	                    is_nothrow_move_constructible_v<T>));
 *
 *	constexpr friend void swap(inplace_vector& x, inplace_vector& y)
 *	noexcept(N == 0 || (is_nothrow_swappable_v<T> &&
 *	                    is_nothrow_move_constructible_v<T>))
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace swap_test
{

struct S1
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S1(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S1()                     = default;
	HAMON_CXX20_CONSTEXPR S1(S1 const&)            = default;
	HAMON_CXX20_CONSTEXPR S1(S1&&)                 = default;
	HAMON_CXX20_CONSTEXPR S1& operator=(S1 const&) = default;
	HAMON_CXX20_CONSTEXPR S1& operator=(S1&&)      = default;
	HAMON_CXX20_CONSTEXPR ~S1()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S1 const& y) const { return m_value == y.m_value; }
};
static_assert( hamon::is_nothrow_swappable<S1>::value, "");
static_assert( hamon::is_nothrow_move_constructible<S1>::value, "");

struct S2
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S2(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S2()                     = default;
	HAMON_CXX20_CONSTEXPR S2(S2 const&)            = default;
	HAMON_CXX20_CONSTEXPR S2(S2&& x) : m_value(x.m_value) {}
	HAMON_CXX20_CONSTEXPR S2& operator=(S2 const&) = default;
	HAMON_CXX20_CONSTEXPR S2& operator=(S2&&)      = default;
	HAMON_CXX20_CONSTEXPR ~S2()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S2 const& y) const { return m_value == y.m_value; }
};
static_assert(!hamon::is_nothrow_swappable<S2>::value, "");
static_assert(!hamon::is_nothrow_move_constructible<S2>::value, "");

struct S3
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S3(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S3()                     = default;
	HAMON_CXX20_CONSTEXPR S3(S3 const&)            = default;
	HAMON_CXX20_CONSTEXPR S3(S3&&)                 = default;
	HAMON_CXX20_CONSTEXPR S3& operator=(S3 const&) = default;
	HAMON_CXX20_CONSTEXPR S3& operator=(S3&& x) { m_value = x.m_value; return *this; }
	HAMON_CXX20_CONSTEXPR ~S3()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S3 const& y) const { return m_value == y.m_value; }
};
static_assert(!hamon::is_nothrow_swappable<S3>::value, "");
static_assert( hamon::is_nothrow_move_constructible<S3>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v1;
		InplaceVector v2;
		VERIFY(v1.empty());
		VERIFY(v2.empty());

		v1.swap(v2);
		VERIFY(v1.empty());
		VERIFY(v2.empty());

		swap(v1, v2);
		VERIFY(v1.empty());
		VERIFY(v2.empty());
	}

	return true;
}

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_3()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v1{T{1}, T{2}, T{3}};
		InplaceVector v2{T{4}, T{5}};
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == T{1});
		VERIFY(v1[1] == T{2});
		VERIFY(v1[2] == T{3});
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == T{4});
		VERIFY(v2[1] == T{5});

		v1.swap(v2);
		VERIFY(v1.size() == 2);
		VERIFY(v1[0] == T{4});
		VERIFY(v1[1] == T{5});
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == T{1});
		VERIFY(v2[1] == T{2});
		VERIFY(v2[2] == T{3});

		swap(v1, v2);
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == T{1});
		VERIFY(v1[1] == T{2});
		VERIFY(v1[2] == T{3});
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == T{4});
		VERIFY(v2[1] == T{5});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 3>()));
	VERIFY((test_impl_0<T, 5>()));
	VERIFY((test_impl_0<T, 6>()));
	VERIFY((test_impl_0<T, 10>()));

//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 5>()));
	VERIFY((test_impl_3<T, 6>()));
	VERIFY((test_impl_3<T, 10>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S3>());

	{
		using InplaceVector = hamon::inplace_vector<int, 0>;
		InplaceVector v;
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 1>;
		InplaceVector v;
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S1, 0>;
		InplaceVector v;
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S1, 1>;
		InplaceVector v;
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S2, 0>;
		InplaceVector v;
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S2, 1>;
		InplaceVector v;
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S3, 0>;
		InplaceVector v;
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S3, 1>;
		InplaceVector v;
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
	}

	// https://en.cppreference.com/w/cpp/container/inplace_vector/swap
	{
		auto print = [](hamon::inplace_vector<int, 3> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<int, 3> a1 {1, 2, 3}, a2 {4, 5, 6};

		auto i1 = a1.begin();
		auto i2 = a2.begin();
		int& r1 = a1[1];
		int& r2 = a2[1];

		// Before swap
		EXPECT_EQ("1, 2, 3, ", print(a1));
		EXPECT_EQ("4, 5, 6, ", print(a2));
		EXPECT_EQ(1, *i1);
		EXPECT_EQ(4, *i2);
		EXPECT_EQ(2, r1);
		EXPECT_EQ(5, r2);

		a1.swap(a2);

		// After swap
		EXPECT_EQ("4, 5, 6, ", print(a1));
		EXPECT_EQ("1, 2, 3, ", print(a2));
		EXPECT_EQ(4, *i1);
		EXPECT_EQ(1, *i2);
		EXPECT_EQ(5, r1);
		EXPECT_EQ(2, r2);

		// Note that after swap() iterators and references stay associated with their
		// original sites, e.g., i1 points to element a1[0], r1 refers to a1[1].
	}
}

}	// namespace swap_test

}	// namespace hamon_inplace_vector_test
