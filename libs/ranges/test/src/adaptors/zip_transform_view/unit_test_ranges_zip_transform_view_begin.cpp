/**
 *	@file	unit_test_ranges_zip_transform_view_begin.cpp
 *
 *	@brief	begin() のテスト
 *
 *	constexpr auto begin();
 *	constexpr auto begin() const
 *	  requires range<const InnerView> &&
 *	           regular_invocable<const F&, range_reference_t<const Views>...>;
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
namespace begin_test
{

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

struct F1
{
	constexpr int const& operator()(int const& r) const { return r; }
};

struct F2
{
	constexpr int& operator()(int& r) const { return r; }
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

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using F = Add;

		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		static_assert( has_begin<ZV&>::value, "");
		static_assert( has_begin<ZV const&>::value, "");

		using I  = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		//static_assert(hamon::is_same<I,  ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, ZV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");

		F f{};
		int a1[] = { 1,2,3 };
		int a2[] = { 4,5,6 };
		V1 v1(a1);
		V2 v2(a2);
		{
			ZV zv(f, v1, v2);
			auto it = zv.begin();
			VERIFY(*it == 5);
		}
		{
			ZV const zv(f, v1, v2);
			auto it = zv.begin();
			VERIFY(*it == 5);
		}
	}
	{
		using F = F1;

		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( has_begin<ZV&>::value, "");
		static_assert( has_begin<ZV const&>::value, "");

		using I  = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		//static_assert(hamon::is_same<I,  ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, ZV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");
	}
	{
		using F = F2;

		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( has_begin<ZV&>::value, "");
		static_assert( has_begin<ZV const&>::value, "");

		using I  = decltype(hamon::declval<ZV&>().begin());
		using CI = decltype(hamon::declval<ZV const&>().begin());
		//static_assert(hamon::is_same<I,  ZV::iterator<false>>::value, "");
		//static_assert(hamon::is_same<CI, ZV::iterator<true>>::value, "");
		static_assert(!hamon::is_same<I, CI>::value, "");
	}

	// MSVC-STLの実装がSFINAE-friendlyになっていない
#if !defined(HAMON_USE_STD_RANGES_ZIP_TRANSFORM_VIEW) && defined(HAMON_STDLIB_DINKUMWARE)
	// !ranges::range<InnerView const>
	{
		using F = Add;

		using V1 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int>
		>;

		using V2 = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		static_assert( has_begin<ZV&>::value, "");
		static_assert(!has_begin<ZV const&>::value, "");

		//using I  = decltype(hamon::declval<ZV&>().begin());
		//static_assert(hamon::is_same<I,  ZV::iterator<false>>::value, "");
	}
#endif

	// !regular_invocable<F const&, range_reference_t<Views const>...>
	{
		using F = F2;

		using V = TestView<int,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int>,
			input_iterator_wrapper<int const>,
			input_iterator_wrapper<int const>
		>;

		using ZV = hamon::ranges::zip_transform_view<F, V>;
		static_assert( has_begin<ZV&>::value, "");
		static_assert(!has_begin<ZV const&>::value, "");

		//using I  = decltype(hamon::declval<ZV&>().begin());
		//static_assert(hamon::is_same<I,  ZV::iterator<false>>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace begin_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
