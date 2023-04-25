/**
 *	@file	unit_test_tuple_tie.cpp
 *
 *	@brief	tie のテスト
 *
 *	template<class... TTypes>
 *	constexpr tuple<TTypes&...> tie(TTypes&... t) noexcept;
 */

#include <hamon/tuple/tie.hpp>
#include <hamon/tuple/make_tuple.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace tie_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i {};
		float f {};
		hamon::tie(i, hamon::ignore, f) = hamon::make_tuple(42, 3.14, 0.5f);
		VERIFY(i == 42);
		VERIFY(f == 0.5f);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, TieTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

	{
		int a = 1;
		char b = 'a';
		std::string c = "Hello";
		auto t = hamon::tie(a, b, c);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int&, char&, std::string&>>::value, "");
	}
	{
		hamon::tuple<int, char, std::string> t(1, 'a', "Hello");
		int a = 0;
		char b = 0;
		std::string c;
		hamon::tie(a, b, c) = t;
		EXPECT_TRUE(a == 1);
		EXPECT_TRUE(b == 'a');
		EXPECT_TRUE(c == "Hello");
	}
}

}	// namespace tie_test

}	// namespace hamon_tuple_test
