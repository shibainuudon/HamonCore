/**
 *	@file	unit_test_ranges_lazy_split_view_inner_iterator_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr explicit inner-iterator(outer-iterator<Const> i);
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace inner_iterator_ctor_conv_test
{

template <
	typename T,
	typename Iterator,
	typename ConstIterator,
	typename Sentinel = test_sentinel<Iterator>,
	typename ConstSentinel = test_sentinel<ConstIterator>
>
struct NotSimpleView : hamon::ranges::view_base
{
	T* m_first;
	T* m_last;

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	using sentinel = Sentinel;
	using const_sentinel = ConstSentinel;

	HAMON_CXX11_CONSTEXPR NotSimpleView() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR NotSimpleView(T (&arr)[N]) : NotSimpleView(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR NotSimpleView(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR iterator       begin()       noexcept { return iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept { return const_iterator{m_first}; }
	HAMON_CXX14_CONSTEXPR sentinel       end()         noexcept { return sentinel{iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR const_sentinel end()   const noexcept { return const_sentinel{const_iterator{m_last}}; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = NotSimpleView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int const>>;
	using P = NotSimpleView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>>;
	using RV = hamon::ranges::lazy_split_view<V, P>;
	using OuterIter      = decltype(hamon::declval<RV&>().begin());
	using ConstOuterIter = decltype(hamon::declval<RV const&>().begin());
	using InnerRng       = decltype(*hamon::declval<OuterIter&>());
	using ConstInnerRng  = decltype(*hamon::declval<ConstOuterIter&>());
	using InnerIter      = decltype(hamon::declval<InnerRng&>().begin());
	using ConstInnerIter = decltype(hamon::declval<ConstInnerRng&>().begin());
	static_assert(!hamon::is_same<InnerIter, ConstInnerIter>::value, "");
	static_assert( hamon::is_constructible<InnerIter, OuterIter>::value, "");
	static_assert(!hamon::is_constructible<InnerIter, ConstOuterIter>::value, "");
	static_assert(!hamon::is_constructible<ConstInnerIter, OuterIter>::value, "");
	static_assert( hamon::is_constructible<ConstInnerIter, ConstOuterIter>::value, "");

	int a1[] = {1, 2, 3, 0, 4, 5};
	int a2[] = {0};
	V v(a1);
	P p(a2);
	RV rv(v, p);
	RV const& crv = rv;
	{
		InnerIter i{rv.begin()};
		VERIFY(*i == 1);
	}
	{
		ConstInnerIter i{crv.begin()};
		VERIFY(*i == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewInnerIteratorCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace inner_iterator_ctor_conv_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
