/**
 *	@file	unit_test_ranges_zip_transform_view_sentinel_sub.cpp
 *
 *	@brief	operator- のテスト
 *
 *	template<bool OtherConst>
 *	  requires sized_sentinel_for<zentinel<Const>, ziperator<OtherConst>>
 *	friend constexpr range_difference_t<maybe-const<OtherConst, InnerView>>
 *	operator-(const iterator<OtherConst>& x, const sentinel& y);
 *
 *	template<bool OtherConst>
 *	  requires sized_sentinel_for<zentinel<Const>, ziperator<OtherConst>>
 *	friend constexpr range_difference_t<maybe-const<OtherConst, InnerView>>
 *	operator-(const sentinel& x, const iterator<OtherConst>& y);
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace sentinel_sub_test
{

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR TestIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR TestIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type operator-(TestIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&              operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&              operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const TestIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const TestIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const TestIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const TestIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
HAMON_CXX14_CONSTEXPR TestIterator<T>
operator+(hamon::ptrdiff_t, TestIterator<T> const&);

template <typename Iterator>
struct ConvertibleSentinel
{
	Iterator m_it;

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel() : m_it() {}

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel(Iterator const& it) : m_it(it) {}
};

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(ConvertibleSentinel<T> const& x, U const& y) noexcept
{
	return base(x.m_it) == base(y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(ConvertibleSentinel<T> const& x, U const& y) noexcept
{
	return !(x == y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(T const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return y == x;
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(T const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return !(x == y);
}

template <typename T, typename U>
HAMON_CONSTEXPR auto
operator-(ConvertibleSentinel<T> const& s, U const& i) noexcept
->decltype(base(s.m_it) - base(i))
{
	return base(s.m_it) - base(i);
}

template <typename T, typename U>
HAMON_CONSTEXPR auto
operator-(T const& i, ConvertibleSentinel<U> const& s) noexcept
->decltype(base(i) - base(s.m_it))
{
	return base(i) - base(s.m_it);
}

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
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{Iterator{m_last}}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{ConstIterator{m_last}}; }
};

template <typename T, typename U, typename = void>
struct has_sub
	: public hamon::false_type {};

template <typename T, typename U>
struct has_sub<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// iterator<true>, sentinel<true>
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>
		>;
		using V2 = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV const&>().begin());
		using S = decltype(hamon::declval<ZV const&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<true>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a1[] = {10,20,30};
		int a2[] = {1,2};
		V1 v1(a1);
		V2 v2(a2);
		ZV zv(F{}, v1, v2);
		I i = zv.begin();
		S s = zv.end();
		VERIFY(i - s == -2);
		VERIFY(s - i ==  2);
	}
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>
		>;
		using V2 = TestView<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV const&>().begin());
		using S = decltype(hamon::declval<ZV const&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<true>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}

	// iterator<false>, sentinel<true>
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int const>,
			ConvertibleSentinel<TestIterator<int const>>
		>;

		using V2 = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV&>().begin());
		using S = decltype(hamon::declval<ZV const&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<true>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a1[] = {10,20,30};
		int a2[] = {1,2,3,4,5};
		V1 v1(a1);
		V2 v2(a2);
		ZV zv(F{}, v1, v2);
		ZV const& czv = zv;
		I i = zv.begin();
		S s = czv.end();
		VERIFY(i - s == -3);
		VERIFY(s - i ==  3);
	}
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int const>,
			ConvertibleSentinel<TestIterator<int const>>
		>;

		using V2 = TestView<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV&>().begin());
		using S = decltype(hamon::declval<ZV const&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<true>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}

	// iterator<true>, sentinel<false>
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int const>,
			ConvertibleSentinel<TestIterator<int const>>
		>;

		using V2 = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV const&>().begin());
		using S = decltype(hamon::declval<ZV&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<false>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a1[] = {10,20,30,40};
		int a2[] = {1,2,3,4,5};
		V1 v1(a1);
		V2 v2(a2);
		ZV zv(F{}, v1, v2);
		ZV const& czv = zv;
		I i = czv.begin();
		S s = zv.end();
		VERIFY(i - s == -4);
		VERIFY(s - i ==  4);
	}
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int const>,
			ConvertibleSentinel<TestIterator<int const>>
		>;

		using V2 = TestView<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV const&>().begin());
		using S = decltype(hamon::declval<ZV&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<true>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<false>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}

	// iterator<false>, sentinel<false>
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int const>,
			ConvertibleSentinel<TestIterator<int const>>
		>;

		using V2 = TestView<int,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>,
			random_access_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV&>().begin());
		using S = decltype(hamon::declval<ZV&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<false>>::value, "");

		static_assert( has_sub<I, S>::value, "");
		static_assert( has_sub<S, I>::value, "");

		int a1[] = {10,20,30,40,50};
		int a2[] = {1,2,3,4};
		V1 v1(a1);
		V2 v2(a2);
		ZV zv(F{}, v1, v2);
		I i = zv.begin();
		S s = zv.end();
		VERIFY(i - s == -4);
		VERIFY(s - i ==  4);
	}
	{
		using F = Add;
		using V1 = TestView<int,
			TestIterator<int>,
			ConvertibleSentinel<TestIterator<int>>,
			TestIterator<int const>,
			ConvertibleSentinel<TestIterator<int const>>
		>;

		using V2 = TestView<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;

		using I = decltype(hamon::declval<ZV&>().begin());
		using S = decltype(hamon::declval<ZV&>().end());
		//static_assert(hamon::is_same<I, ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<S, ZV::sentinel<false>>::value, "");

		static_assert(!has_sub<I, S>::value, "");
		static_assert(!has_sub<S, I>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewSentinelSubTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace sentinel_sub_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
