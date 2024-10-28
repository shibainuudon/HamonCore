/**
 *	@file	unit_test_inplace_vector_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	constexpr ~inplace_vector();
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace dtor_test
{

struct S1
{
	~S1() = default;
};
static_assert( hamon::is_trivially_destructible<S1>::value, "");

struct S2
{
	static int s_dtor_count;
	~S2() {++s_dtor_count;}
};
static_assert(!hamon::is_trivially_destructible<S2>::value, "");

int S2::s_dtor_count = 0;

GTEST_TEST(InplaceVectorTest, DtorTest)
{
	{
		using InplaceVector = hamon::inplace_vector<int, 0>;
		static_assert( hamon::is_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_nothrow_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_trivially_destructible<InplaceVector>::value, "");
	}
	{
		using InplaceVector = hamon::inplace_vector<int, 5>;
		static_assert( hamon::is_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_nothrow_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_trivially_destructible<InplaceVector>::value, "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S1, 0>;
		static_assert( hamon::is_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_nothrow_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_trivially_destructible<InplaceVector>::value, "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S1, 5>;
		static_assert( hamon::is_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_nothrow_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_trivially_destructible<InplaceVector>::value, "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S2, 0>;
		static_assert( hamon::is_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_nothrow_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_trivially_destructible<InplaceVector>::value, "");
	}
	{
		using InplaceVector = hamon::inplace_vector<S2, 5>;
		static_assert( hamon::is_destructible<InplaceVector>::value, "");
		static_assert( hamon::is_nothrow_destructible<InplaceVector>::value, "");
		static_assert(!hamon::is_trivially_destructible<InplaceVector>::value, "");
	}

	S2::s_dtor_count = 0;
	{
		using InplaceVector = hamon::inplace_vector<S2, 5>;
		InplaceVector v;
	}
	EXPECT_EQ(0, S2::s_dtor_count);

	S2::s_dtor_count = 0;
	{
		using InplaceVector = hamon::inplace_vector<S2, 5>;
		InplaceVector v(3);
	}
	EXPECT_EQ(3, S2::s_dtor_count);
}

}	// namespace dtor_test

}	// namespace hamon_inplace_vector_test
