/**
 *	@file	unit_test_inplace_vector_op_assign_move.cpp
 *
 *	@brief	代入演算子のテスト
 *
 *	constexpr inplace_vector& operator=(inplace_vector&& other)
 *		noexcept(N == 0 || (is_nothrow_move_assignable_v<T> &&
 *						    is_nothrow_move_constructible_v<T>));
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace op_assign_move_test
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
static_assert( hamon::is_trivially_destructible<S1>::value, "");
static_assert( hamon::is_trivially_move_constructible<S1>::value, "");
static_assert( hamon::is_trivially_move_assignable<S1>::value, "");

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
static_assert( hamon::is_trivially_destructible<S2>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S2>::value, "");
static_assert( hamon::is_trivially_move_assignable<S2>::value, "");

struct S3
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S3(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S3()                     = default;
	HAMON_CXX20_CONSTEXPR S3(S3 const&)            = default;
	HAMON_CXX20_CONSTEXPR S3(S3&&)                 = default;
	HAMON_CXX20_CONSTEXPR S3& operator=(S3 const&) = default;
	HAMON_CXX20_CONSTEXPR S3& operator=(S3&& x)    { m_value = x.m_value; return *this; }
	HAMON_CXX20_CONSTEXPR ~S3()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S3 const& y) const { return m_value == y.m_value; }
};
static_assert( hamon::is_trivially_destructible<S3>::value, "");
static_assert( hamon::is_trivially_move_constructible<S3>::value, "");
static_assert(!hamon::is_trivially_move_assignable<S3>::value, "");

struct S4
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S4(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S4()                     = default;
	HAMON_CXX20_CONSTEXPR S4(S4 const&)            = default;
	HAMON_CXX20_CONSTEXPR S4(S4&&)                 = default;
	HAMON_CXX20_CONSTEXPR S4& operator=(S4 const&) = delete;
	HAMON_CXX20_CONSTEXPR S4& operator=(S4&& x)    { m_value = x.m_value; return *this; }
	HAMON_CXX20_CONSTEXPR ~S4()                    = default;
	HAMON_CXX20_CONSTEXPR bool operator==(S4 const& y) const { return m_value == y.m_value; }
};
static_assert( hamon::is_trivially_destructible<S4>::value, "");
static_assert( hamon::is_trivially_move_constructible<S4>::value, "");
static_assert(!hamon::is_trivially_move_assignable<S4>::value, "");

struct S5
{
	int m_value;
	HAMON_CXX20_CONSTEXPR S5(int v) : m_value(v) {}
	HAMON_CXX20_CONSTEXPR S5()                     = default;
	HAMON_CXX20_CONSTEXPR S5(S5 const&)            = default;
	HAMON_CXX20_CONSTEXPR S5(S5&&)                 = default;
	HAMON_CXX20_CONSTEXPR S5& operator=(S5 const&) = default;
	HAMON_CXX20_CONSTEXPR S5& operator=(S5&&)      = default;
	HAMON_CXX20_CONSTEXPR ~S5()                    {}
	HAMON_CXX20_CONSTEXPR bool operator==(S5 const& y) const { return m_value == y.m_value; }
};
static_assert(!hamon::is_trivially_destructible<S5>::value, "");
static_assert(!hamon::is_trivially_move_constructible<S5>::value, "");
static_assert( hamon::is_trivially_move_assignable<S5>::value, "");

static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<int, 0>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<int, 1>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<float, 0>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<float, 1>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<S1, 0>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<S1, 1>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<S2, 0>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::inplace_vector<S2, 1>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<S3, 0>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::inplace_vector<S3, 1>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<S4, 0>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::inplace_vector<S4, 1>>::value, "");
static_assert( hamon::is_trivially_move_assignable<hamon::inplace_vector<S5, 0>>::value, "");
static_assert(!hamon::is_trivially_move_assignable<hamon::inplace_vector<S5, 1>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v1;
		InplaceVector v2;
		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
		{
			auto& r = (v2 = hamon::move(v1));
			VERIFY(&r != &v1);
			VERIFY(&r == &v2);
		}
		VERIFY(v2.empty());
		VERIFY(v2.size() == 0);
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
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == T{4});
		VERIFY(v2[1] == T{5});
		{
			auto& r = (v2 = hamon::move(v1));
			VERIFY(&r != &v1);
			VERIFY(&r == &v2);
		}
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == T{1});
		VERIFY(v2[1] == T{2});
		VERIFY(v2[2] == T{3});
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 2>()));
	VERIFY((test_impl_0<T, 3>()));
	VERIFY((test_impl_0<T, 9>()));

//	VERIFY((test_impl_3<T, 0>()));
//	VERIFY((test_impl_3<T, 1>()));
//	VERIFY((test_impl_3<T, 2>()));
	VERIFY((test_impl_3<T, 3>()));
	VERIFY((test_impl_3<T, 9>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, OpAssignMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
#if defined(HAMON_MSVC) && (HAMON_MSVC < 1930)
	EXPECT_TRUE(test<S2>());
	EXPECT_TRUE(test<S3>());
	EXPECT_TRUE(test<S4>());
#else
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S3>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S4>());
#endif
	EXPECT_TRUE(test<S5>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/operator%3D
	{
		auto print = [](hamon::inplace_vector<hamon::string, 3> const& v)
		{
			std::stringstream ss;
			for (auto const& e : v)
			{
				ss << e << ", ";
			}
			return ss.str();
		};

		hamon::inplace_vector<hamon::string, 3> z, w{"CAT", "GREEN HEART"};
		// Initially
		EXPECT_EQ("",                   print(z));
		EXPECT_EQ("CAT, GREEN HEART, ", print(w));

		// Move assignment moves data from w to z
		z = hamon::move(w); // overload (2)
		EXPECT_EQ("CAT, GREEN HEART, ", print(z));
//		EXPECT_EQ("",                   print(w));	// w is invalid but unspecified state
	}
}

}	// namespace op_assign_move_test

}	// namespace hamon_inplace_vector_test
