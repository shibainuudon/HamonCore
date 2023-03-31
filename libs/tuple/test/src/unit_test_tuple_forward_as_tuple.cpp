/**
 *	@file	unit_test_tuple_forward_as_tuple.cpp
 *
 *	@brief	forward_as_tuple のテスト
 *
 *	template<class... TTypes>
 *	constexpr tuple<TTypes&&...>
 *	forward_as_tuple(TTypes&&... t) noexcept;
 */

#include <hamon/tuple.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace forward_as_tuple_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		auto t = hamon::forward_as_tuple();
		static_assert(hamon::is_same<decltype(t), hamon::tuple<>>::value, "");
	}
	{
		auto t = hamon::forward_as_tuple(0.5f);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<float&&>>::value, "");
		VERIFY(get<0>(hamon::forward_as_tuple(0.5f)) == 0.5f);
	}
	{
		auto t = hamon::forward_as_tuple(1, 'a', 2.5);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int&&, char&&, double&&>>::value, "");
		VERIFY(get<0>(hamon::forward_as_tuple(1, 'a', 2.5)) == 1);
		VERIFY(get<1>(hamon::forward_as_tuple(1, 'a', 2.5)) == 'a');
		VERIFY(get<2>(hamon::forward_as_tuple(1, 'a', 2.5)) == 2.5);
	}
	{
		int a = 3;
		const float b = 4.5f;
		auto t = hamon::forward_as_tuple(a, 5, b);
		static_assert(hamon::is_same<decltype(t), hamon::tuple<int&, int&&, const float&>>::value, "");
		VERIFY(get<0>(t) == a);
		VERIFY(get<2>(t) == b);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, ForwardAsTupleTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace forward_as_tuple_test

}	// namespace hamon_tuple_test
