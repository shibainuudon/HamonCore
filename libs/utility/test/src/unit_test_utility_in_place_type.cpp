/**
 *	@file	unit_test_utility_in_place_type.cpp
 *
 *	@brief	in_place_type のテスト
 */

#include <hamon/utility/in_place_type_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace in_place_type_test
{

struct Foo
{
	HAMON_CXX11_CONSTEXPR Foo(hamon::size_t i)
		: m_in_place_initialized(false)
		, m_value(i)
	{}

	template <typename T>
	HAMON_CXX11_CONSTEXPR Foo(hamon::in_place_type_t<T>)
		: m_in_place_initialized(true)
		, m_value(sizeof(T))
	{}

	bool           m_in_place_initialized;
	hamon::size_t  m_value;
};

GTEST_TEST(UtilityTest, InPlaceTypeTest)
{
	HAMON_CXX11_CONSTEXPR Foo f1(3);
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES) && !defined(_MSC_VER)
	HAMON_CXX11_CONSTEXPR Foo f2(hamon::in_place_type<char>);
#else
	HAMON_CXX11_CONSTEXPR Foo f2(hamon::in_place_type_t<char>{});
#endif

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(f1.m_in_place_initialized);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (f2.m_in_place_initialized);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, f1.m_value);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, f2.m_value);
}

}	// namespace in_place_type_test

}	// namespace hamon_utility_test
