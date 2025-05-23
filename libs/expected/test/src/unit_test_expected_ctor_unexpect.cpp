/**
 *	@file	unit_test_expected_ctor_unexpect.cpp
 *
 *	@brief	unexpect_t を引数に取るコンストラクタのテスト
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_unexpect_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		hamon::expected<T, E> x{hamon::unexpect, E{10}};
		VERIFY(!x.has_value());
		VERIFY(x.error() == E{10});
	}
	return true;
}

struct ComplexType
{
	hamon::string data;
	hamon::vector<int> seq;

	constexpr
	ComplexType(const char* ptr, size_t len)
		: data(ptr, len) {}

	constexpr
	ComplexType(std::initializer_list<int> il, hamon::string_view sv)
		: data(sv), seq(il) {}
};

HAMON_CXX20_CONSTEXPR bool test2()
{
	{
		hamon::expected<int, ComplexType> x {hamon::unexpect, "C++", 1};
		VERIFY(!x.has_value());
		VERIFY(x.error().data == "C");
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	{
		hamon::expected<int, ComplexType> x {hamon::unexpect, {5, 6, 7, 8}, "Steps"};
		VERIFY(!x.has_value());
		VERIFY(x.error().data == "Steps");
		VERIFY((x.error().seq == hamon::vector<int>{5, 6, 7, 8}));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, CtorUnexpectTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3()));
}

}	// namespace ctor_unexpect_test

}	// namespace hamon_expected_test
