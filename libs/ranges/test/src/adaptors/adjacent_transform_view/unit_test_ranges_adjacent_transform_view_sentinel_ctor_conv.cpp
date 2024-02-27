/**
 *	@file	unit_test_ranges_adjacent_transform_view_sentinel_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr sentinel(sentinel<!Const> i)
 *	  requires Const && convertible_to<inner-sentinel<false>, inner-sentinel<Const>>;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
//#include <hamon/type_traits/bool_constant.hpp>
//#include <hamon/type_traits/is_same.hpp>
//#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace sentinel_ctor_conv_test
{

struct F
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestView(T (&arr)[N]) : TestView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int const>,
			test_sentinel<forward_iterator_wrapper<int const>>
		>;

		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using S  = decltype(hamon::declval<AV&>().end());
		using CS = decltype(hamon::declval<AV const&>().end());
		//static_assert( hamon::is_same<S,  AV::sentinel<false>>::value, "");
		//static_assert( hamon::is_same<CS, AV::sentinel<true>>::value, "");
		static_assert(!hamon::is_constructible<S, CS>::value, "");
		static_assert(!hamon::is_constructible<CS, S>::value, "");
	}
	{
		using V = TestView<int,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>,
			forward_iterator_wrapper<int>,
			test_sentinel<forward_iterator_wrapper<int>>
		>;

		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		using S  = decltype(hamon::declval<AV&>().end());
		using CS = decltype(hamon::declval<AV const&>().end());
		//static_assert( hamon::is_same<S,  AV::sentinel<false>>::value, "");
		//static_assert( hamon::is_same<CS, AV::sentinel<true>>::value, "");
		static_assert(!hamon::is_constructible<S, CS>::value, "");
		static_assert( hamon::is_constructible<CS, S>::value, "");
		static_assert( hamon::is_implicitly_constructible<CS, S>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		AV av(v, F{});

		CS sent = av.end();
		VERIFY(sent != av.begin());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewSentinelCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_ctor_conv_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
