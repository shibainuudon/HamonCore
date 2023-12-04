/**
 *	@file	unit_test_variant_dtor.cpp
 *
 *	@brief	~variant() のテスト
 */

#include <hamon/variant.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_variant_test
{

namespace dtor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NonTriviallyDtor
{
	HAMON_CXX11_CONSTEXPR NonTriviallyDtor(int* ptr) : m_ptr(ptr) {}
	HAMON_CXX20_CONSTEXPR ~NonTriviallyDtor() { ++(*m_ptr); }
	int* m_ptr;
};
static_assert(!hamon::is_trivially_destructible<NonTriviallyDtor>::value, "");

struct TriviallyDtor
{
	TriviallyDtor(const TriviallyDtor &) {} // non-trivial copy
	~TriviallyDtor() = default;
};
static_assert(!hamon::is_trivially_copy_constructible<TriviallyDtor>::value, "");
static_assert( hamon::is_trivially_destructible<TriviallyDtor>::value, "");

static_assert( hamon::is_trivially_destructible<hamon::variant<int>>::value, "");
static_assert( hamon::is_trivially_destructible<hamon::variant<TriviallyDtor>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::variant<NonTriviallyDtor>>::value, "");
static_assert( hamon::is_trivially_destructible<hamon::variant<int, TriviallyDtor>>::value, "");
static_assert( hamon::is_trivially_destructible<hamon::variant<TriviallyDtor, int>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::variant<int, NonTriviallyDtor>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::variant<NonTriviallyDtor, int>>::value, "");
static_assert( hamon::is_trivially_destructible<hamon::variant<int, long, TriviallyDtor>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::variant<int, long, NonTriviallyDtor>>::value, "");

inline /*HAMON_CXX20_CONSTEXPR*/ bool DtorTest()
{
	{
		using V = hamon::variant<NonTriviallyDtor, int>;
		static_assert(!hamon::is_trivially_destructible<V>::value, "");

		int count1 = 0;
		int count2 = 0;
		{
			V v(hamon::in_place_index_t<0>{}, &count1);
			VERIFY(count1 == 0);
			VERIFY(count2 == 0);
		}
		VERIFY(count1 == 1);
		VERIFY(count2 == 0);
		{
			V v(hamon::in_place_index_t<1>{});
		}
		VERIFY(count1 == 1);
		VERIFY(count2 == 0);
		{
			V v(hamon::in_place_index_t<0>{}, &count2);
			VERIFY(count1 == 1);
			VERIFY(count2 == 0);
		}
		VERIFY(count1 == 1);
		VERIFY(count2 == 1);
	}
	return true;
}

GTEST_TEST(VariantTest, DtorTest)
{
	// TODO
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(DtorTest());
}

#undef VERIFY

}	// namespace dtor_test

}	// namespace hamon_variant_test
