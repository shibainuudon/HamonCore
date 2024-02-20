/**
 *	@file	unit_test_ranges_zip_transform_view_iterator_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	constexpr iterator(iterator<!Const> i)
 *    requires Const && convertible_to<ziperator<false>, ziperator<Const>>;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
//#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
{
namespace iterator_ctor_conv_test
{

template <typename T>
struct ConvertibleInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleInputIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleInputIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ConvertibleInputIterator(ConvertibleInputIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                      operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                        operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleInputIterator& rhs) const { return !(*this == rhs); }
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

struct F
{
	constexpr int operator()(int x) const { return x; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I  = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert( hamon::is_constructible<CI, I>::value, "");
		static_assert( hamon::is_implicitly_constructible<CI, I>::value, "");

		F f{};
		int a[] = { 1, 2, 3 };
		V v(a);
		ZV zv(f, v);
		CI it = zv.begin();
		VERIFY(*it == 1);
	}
	{
		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I  = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert(!hamon::is_constructible<CI, I>::value, "");
	}
	{
		using V = TestView<int,
			ConvertibleInputIterator<int>,
			ConvertibleInputIterator<int>,
			ConvertibleInputIterator<int const>,
			ConvertibleInputIterator<int const>
		>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		using I  = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		static_assert(!hamon::is_same<I, CI>::value, "");
		static_assert(!hamon::is_constructible<I, CI>::value, "");
		static_assert( hamon::is_constructible<CI, I>::value, "");
		static_assert( hamon::is_implicitly_constructible<CI, I>::value, "");

		F f{};
		int a[] = { 1, 2, 3 };
		V v(a);
		ZV zv(f, v);
		CI it = zv.begin();
		VERIFY(*it == 1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewIteratorCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_conv_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
