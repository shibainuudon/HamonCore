/**
 *	@file	unit_test_ranges_join_with_view_iterator_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	iterator() = default;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_ctor_default_test
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
	using I = hamon::ranges::iterator_t<RV>;
	static_assert(hamon::is_default_constructible<I>::value, "");
	I it1{};
	I it2{};
	VERIFY(it1 == it2);
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

GTEST_TEST(RangesTest, JoinWithViewIteratorCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace iterator_ctor_default_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
