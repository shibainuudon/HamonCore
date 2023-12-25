/**
 *	@file	unit_test_ranges_join_view_sentinel_compare.cpp
 *
 *	@brief	operator== のテスト
 *
 *	friend constexpr bool operator==(const iterator<OtherConst>& x, const sentinel& y);
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
namespace sentinel_compare_test
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
	template <typename U>
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleForwardIterator<U>& rhs) const { return m_ptr == rhs.m_ptr; }
	template <typename U>
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleForwardIterator<U>& rhs) const { return !(*this == rhs); }
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

template <typename T, typename U, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_not_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using InnerView = test_forward_common_view<int>;
	using View = test_input_common_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	RV rv(v);

	auto it = rv.begin();
	VERIFY(!(it == rv.end()));
	VERIFY( (it != rv.end()));
	VERIFY(!(rv.end() == it));
	VERIFY( (rv.end() != it));
	++it;
	VERIFY(!(it == rv.end()));
	VERIFY( (it != rv.end()));
	VERIFY(!(rv.end() == it));
	VERIFY( (rv.end() != it));
	++it;
	VERIFY(!(it == rv.end()));
	VERIFY( (it != rv.end()));
	VERIFY(!(rv.end() == it));
	VERIFY( (rv.end() != it));
	++it;
	VERIFY(!(it == rv.end()));
	VERIFY( (it != rv.end()));
	VERIFY(!(rv.end() == it));
	VERIFY( (rv.end() != it));
	++it;
	VERIFY(!(it == rv.end()));
	VERIFY( (it != rv.end()));
	VERIFY(!(rv.end() == it));
	VERIFY( (rv.end() != it));
	++it;
	VERIFY(!(it == rv.end()));
	VERIFY( (it != rv.end()));
	VERIFY(!(rv.end() == it));
	VERIFY( (rv.end() != it));
	++it;
	VERIFY( (it == rv.end()));
	VERIFY(!(it != rv.end()));
	VERIFY( (rv.end() == it));
	VERIFY(!(rv.end() != it));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_input_view<int>;
	using View = NotSimpleView<
		InnerView,
		ConvertibleForwardIterator<InnerView>,
		ConvertibleForwardIterator<InnerView const>,
		ConvertibleForwardIterator<InnerView>,
		ConvertibleForwardIterator<InnerView const>
	>;
	using RV = hamon::ranges::join_view<View>;
	using I  = decltype(hamon::declval<RV&>().begin());
	using CI = decltype(hamon::declval<RV const&>().begin());
	using S  = decltype(hamon::declval<RV&>().end());
	using CS = decltype(hamon::declval<RV const&>().end());

	static_assert(!hamon::is_same<I, S>::value, "");
	static_assert(!hamon::is_same<CI, CS>::value, "");

	static_assert( has_equal<I, S>::value, "");
	static_assert( has_equal<I, CS>::value, "");
	static_assert( has_equal<CI, S>::value, "");
	static_assert( has_equal<CI, CS>::value, "");

	static_assert( has_equal<S, I>::value, "");
	static_assert( has_equal<CS, I>::value, "");
	static_assert( has_equal<S, CI>::value, "");
	static_assert( has_equal<CS, CI>::value, "");

	static_assert( has_not_equal<I, S>::value, "");
	static_assert( has_not_equal<I, CS>::value, "");
	static_assert( has_not_equal<CI, S>::value, "");
	static_assert( has_not_equal<CI, CS>::value, "");

	static_assert( has_not_equal<S, I>::value, "");
	static_assert( has_not_equal<CS, I>::value, "");
	static_assert( has_not_equal<S, CI>::value, "");
	static_assert( has_not_equal<CS, CI>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using InnerView = test_input_view<int>;
	using View = NotSimpleView<
		InnerView,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>,
		forward_iterator_wrapper<InnerView>,
		forward_iterator_wrapper<InnerView const>
	>;
	using RV = hamon::ranges::join_view<View>;
	using I  = decltype(hamon::declval<RV&>().begin());
	using CI = decltype(hamon::declval<RV const&>().begin());
	using S  = decltype(hamon::declval<RV&>().end());
	using CS = decltype(hamon::declval<RV const&>().end());

	static_assert(!hamon::is_same<I, S>::value, "");
	static_assert(!hamon::is_same<CI, CS>::value, "");

	static_assert( has_equal<I, S>::value, "");
	static_assert(!has_equal<I, CS>::value, "");
	static_assert(!has_equal<CI, S>::value, "");
	static_assert( has_equal<CI, CS>::value, "");

	static_assert( has_equal<S, I>::value, "");
	static_assert(!has_equal<CS, I>::value, "");
	static_assert(!has_equal<S, CI>::value, "");
	static_assert( has_equal<CS, CI>::value, "");

	static_assert( has_not_equal<I, S>::value, "");
	static_assert(!has_not_equal<I, CS>::value, "");
	static_assert(!has_not_equal<CI, S>::value, "");
	static_assert( has_not_equal<CI, CS>::value, "");

	static_assert( has_not_equal<S, I>::value, "");
	static_assert(!has_not_equal<CS, I>::value, "");
	static_assert(!has_not_equal<S, CI>::value, "");
	static_assert( has_not_equal<CS, CI>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewSentinelCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace sentinel_compare_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
