/**
 *	@file	unit_test_ranges_join_with_view_sentinel_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	sentinel() = default;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace sentinel_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <
	template <typename> class PatternView,
	template <typename> class InnerView,
	template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = OuterView<InnerView<int>>;
	using RV = hamon::ranges::join_with_view<V, PatternView<int>>;
	using S = hamon::ranges::sentinel_t<RV>;
	static_assert(hamon::is_default_constructible<S>::value, "");
	S it1{};
	S it2{};
	(void)it1;
	(void)it2;
	return true;
}

template <template <typename> class InnerView, template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test01()
{
	VERIFY(test00<test_forward_view, InnerView, OuterView>());
	VERIFY(test00<test_bidirectional_view, InnerView, OuterView>());
	VERIFY(test00<test_random_access_view, InnerView, OuterView>());

	return true;
}


template <template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test02()
{
	VERIFY(test01<test_input_view, OuterView>());
	VERIFY(test01<test_forward_view, OuterView>());
	VERIFY(test01<test_bidirectional_view, OuterView>());
	VERIFY(test01<test_random_access_view, OuterView>());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test()
{
//	VERIFY(test02<test_input_view>());
	VERIFY(test02<test_forward_view>());
	VERIFY(test02<test_bidirectional_view>());
	VERIFY(test02<test_random_access_view>());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewSentinelCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace sentinel_ctor_default_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
