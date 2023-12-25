/**
 *	@file	unit_test_ranges_join_view_end.cpp
 *
 *	@brief	end のテスト
 *
 *	constexpr auto end();
 *	constexpr auto end() const;
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace end_test
{

template <typename T>
struct ValueForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX11_CONSTEXPR ValueForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ValueForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ValueForwardIterator(ValueForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ValueForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueForwardIterator& rhs) const { return !(*this == rhs); }
};

template <typename T> using ValueForwardView = test_view<T, ValueForwardIterator<T>>;

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

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// requires forward_range<const V>

	using V = test_input_view<test_input_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert(!has_end<RV const&>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// requires is_reference_v<range_reference_t<const V>>

	using V = ValueForwardView<test_input_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert(!has_end<RV const&>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// requires input_range<range_reference_t<const V>>

	using InnerView = NotSimpleView<
		int,
		forward_iterator_wrapper<int>,
		output_iterator_wrapper<int const>
	>;
	using V = NotSimpleView<
		InnerView,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>
	>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert(!has_end<RV const&>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using V = test_forward_common_view<test_forward_common_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::iterator<true>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::iterator<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// iterator<true>
		decltype(hamon::declval<RV const&>().end())	// iterator<true>
	>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV&>().end())		// iterator<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it = rv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it == sent1);
	VERIFY(it == sent2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using InnerView = test_forward_common_view<int>;
	using V = NotSimpleView<
		InnerView,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>
	>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::iterator<false>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::iterator<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// iterator<false>
		decltype(hamon::declval<RV const&>().end())	// iterator<true>
	>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// iterator<false>
	>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV const&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV const&>().end())		// iterator<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it1 = rv.begin();
	auto it2 = crv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it1 == sent1);
	VERIFY(it2 == sent2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	// if constexpr (ranges::forward_range<V>

	using V = test_input_common_view<test_forward_common_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert(!has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto it = rv.begin();
	auto sent = rv.end();
	VERIFY(it == sent);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	// if constexpr (ranges::forward_range<InnerRng>

	using V = test_forward_common_view<test_input_common_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// sentinel<true>
		decltype(hamon::declval<RV const&>().end())	// sentinel<true>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<false>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV const&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV const&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it = rv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it == sent1);
	VERIFY(it == sent2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test07()
{
	// if constexpr (ranges::common_range<V>

	using V = test_forward_view<test_forward_common_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// sentinel<true>
		decltype(hamon::declval<RV const&>().end())	// sentinel<true>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<false>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV const&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV const&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it = rv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it == sent1);
	VERIFY(it == sent2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test08()
{
	// if constexpr (ranges::common_range<InnerRng>

	using V = test_forward_common_view<test_forward_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// sentinel<true>
		decltype(hamon::declval<RV const&>().end())	// sentinel<true>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<false>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV const&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV const&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it = rv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it == sent1);
	VERIFY(it == sent2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test09()
{
	// if constexpr (is_reference_v<InnerRng>

	using V = ValueForwardView<test_input_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert(!has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto it = rv.begin();
	auto sent = rv.end();
	VERIFY(it == sent);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test10()
{
	using InnerView = test_forward_common_view<int>;
	using V = NotSimpleView<
		InnerView,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>
	>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<false>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// sentinel<false>
		decltype(hamon::declval<RV const&>().end())	// sentinel<true>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<false>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV const&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV const&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it1 = rv.begin();
	auto it2 = crv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it1 == sent1);
	VERIFY(it2 == sent2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test11()
{
	using InnerView = test_input_common_view<int>;
	using V = NotSimpleView<
		InnerView,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>
	>;
	using RV = hamon::ranges::join_view<V>;

	static_assert( has_end<RV&>::value, "");
	static_assert( has_end<RV const&>::value, "");

	//static_assert(hamon::is_same<
	//	typename RV::sentinel<false>,
	//	decltype(hamon::declval<RV&>().end())
	//>::value, "");
	//static_assert(hamon::is_same<
	//	typename RV::sentinel<true>,
	//	decltype(hamon::declval<RV const&>().end())
	//>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().end()),		// sentinel<false>
		decltype(hamon::declval<RV const&>().end())	// sentinel<true>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV&>().begin()),	// iterator<false>
		decltype(hamon::declval<RV&>().end())		// sentinel<false>
	>::value, "");

	static_assert(!hamon::is_same<
		decltype(hamon::declval<RV const&>().begin()),	// iterator<true>
		decltype(hamon::declval<RV const&>().end())		// sentinel<true>
	>::value, "");

	RV rv{};
	auto const& crv = rv;
	auto it1 = rv.begin();
	auto it2 = crv.begin();
	auto sent1 = rv.end();
	auto sent2 = crv.end();
	VERIFY(it1 == sent1);
	VERIFY(it2 == sent2);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test08());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test09());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test10());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test11());
}

}	// namespace end_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
