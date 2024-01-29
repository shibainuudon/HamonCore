/**
 *	@file	unit_test_ranges_join_with_view_iterator_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr iterator(iterator<!Const> i)
 *	  requires Const && convertible_to<iterator_t<V>, OuterIter> &&
 *	    convertible_to<iterator_t<InnerRng>, InnerIter> &&
 *	    convertible_to<iterator_t<Pattern>, PatternIter>;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_ctor_conv_test
{

template <typename T>
struct ConvertibleForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(ConvertibleForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T& operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleForwardIterator& rhs) const { return !(*this == rhs); }
};

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
	{
		using InnerView = NotSimpleView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>>;
		using V = NotSimpleView<InnerView,
			ConvertibleForwardIterator<InnerView>,
			ConvertibleForwardIterator<InnerView const>>;
		using Pattern = NotSimpleView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>>;

		using InnerRng = hamon::ranges::range_reference_t<V>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<V>, hamon::ranges::iterator_t<V const>>::value, "");
		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<InnerRng>, hamon::ranges::iterator_t<InnerConstRng>>::value, "");
		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<Pattern>, hamon::ranges::iterator_t<Pattern const>>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		using CI = hamon::ranges::iterator_t<RV const>;
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert( hamon::is_constructible<CI, I>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
	}
	{
		using InnerView = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;
		using V = NotSimpleView<InnerView,
			ConvertibleForwardIterator<InnerView>,
			ConvertibleForwardIterator<InnerView const>>;
		using Pattern = NotSimpleView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>>;

		using InnerRng = hamon::ranges::range_reference_t<V>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<V>, hamon::ranges::iterator_t<V const>>::value, "");
		static_assert(!hamon::convertible_to_t<hamon::ranges::iterator_t<InnerRng>, hamon::ranges::iterator_t<InnerConstRng>>::value, "");
		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<Pattern>, hamon::ranges::iterator_t<Pattern const>>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		using CI = hamon::ranges::iterator_t<RV const>;
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
	}
	{
		using InnerView = NotSimpleView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>>;
		using V = NotSimpleView<InnerView,
			forward_iterator_wrapper<InnerView>,
			forward_iterator_wrapper<InnerView const>>;
		using Pattern = NotSimpleView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>>;

		using InnerRng = hamon::ranges::range_reference_t<V>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert(!hamon::convertible_to_t<hamon::ranges::iterator_t<V>, hamon::ranges::iterator_t<V const>>::value, "");
		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<InnerRng>, hamon::ranges::iterator_t<InnerConstRng>>::value, "");
		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<Pattern>, hamon::ranges::iterator_t<Pattern const>>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		using CI = hamon::ranges::iterator_t<RV const>;
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
	}
	{
		using InnerView = NotSimpleView<int,
			ConvertibleForwardIterator<int>,
			ConvertibleForwardIterator<int const>>;
		using V = NotSimpleView<InnerView,
			ConvertibleForwardIterator<InnerView>,
			ConvertibleForwardIterator<InnerView const>>;
		using Pattern = NotSimpleView<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int const>>;

		using InnerRng = hamon::ranges::range_reference_t<V>;
		using InnerConstRng = hamon::ranges::range_reference_t<const V>;

		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<V>, hamon::ranges::iterator_t<V const>>::value, "");
		static_assert( hamon::convertible_to_t<hamon::ranges::iterator_t<InnerRng>, hamon::ranges::iterator_t<InnerConstRng>>::value, "");
		static_assert(!hamon::convertible_to_t<hamon::ranges::iterator_t<Pattern>, hamon::ranges::iterator_t<Pattern const>>::value, "");

		using RV = hamon::ranges::join_with_view<V, Pattern>;
		using I = hamon::ranges::iterator_t<RV>;
		using CI = hamon::ranges::iterator_t<RV const>;
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_input_view<int>;
	using V = NotSimpleView<InnerView,
		ConvertibleForwardIterator<InnerView>,
		ConvertibleForwardIterator<InnerView const>>;
	using Pattern = NotSimpleView<int,
		forward_iterator_wrapper<int>,
		forward_iterator_wrapper<int>>;

	using RV = hamon::ranges::join_with_view<V, Pattern>;
	//static_assert(hamon::is_same<decltype(hamon::declval<RV&>().begin()), typename RV::iterator<false>>::value, "");
	//static_assert(hamon::is_same<decltype(hamon::declval<RV const&>().begin()), typename RV::iterator<true>>::value, "");

	using I = hamon::ranges::iterator_t<RV>;
	using CI = hamon::ranges::iterator_t<RV const>;

	int a0[] = {1};
	int a1[] = {2,3};
	int a2[] = {4,5,6};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	V v(iv);
	int a3[] = {-1,-2};
	Pattern pat(a3);

	RV rv(v, pat);
	I it = rv.begin();
	{
		CI it2 = it;
		VERIFY(*it2 == 1);
	}
	++it;
	{
		CI it2 = it;
		VERIFY(*it2 == -1);
	}
	++it;
	{
		CI it2 = it;
		VERIFY(*it2 == -2);
	}
	++it;
	{
		CI it2 = it;
		VERIFY(*it2 == 2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace iterator_ctor_conv_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
