/**
 *	@file	unit_test_ranges_zip_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires (sized_range<Views> && ...);
 *	constexpr auto size() const requires (sized_range<const Views> && ...);
 */

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_view_test
{
namespace size_test
{

template <typename D1, typename D2>
struct TestSizedView : hamon::ranges::view_base
{
	using Iterator = bidirectional_iterator_wrapper<int>;
	using Sentinel = test_sentinel<Iterator>;
	Iterator begin() const noexcept;
	Sentinel end()   const noexcept;

	D1 size() noexcept;
	D2 size() const noexcept;
};

template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// (sized_range<Views> && ...) && (sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<int, short>;
		using V2 = TestSizedView<char, short>;
		static_assert( hamon::ranges::sized_range_t<V1>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2>::value, "");
		static_assert( hamon::ranges::sized_range_t<V1 const>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2 const>::value, "");

		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( has_size<ZV&>::value, "");
		static_assert( has_size<ZV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<ZV&>().size()), unsigned int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<ZV const&>().size()), unsigned short>::value, "");
	}
	
	// !(sized_range<Views> && ...) && (sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<void, char>;
		using V2 = TestSizedView<int, short>;
		static_assert(!hamon::ranges::sized_range_t<V1>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2>::value, "");
		static_assert( hamon::ranges::sized_range_t<V1 const>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2 const>::value, "");

		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( has_size<ZV&>::value, "");
		static_assert( has_size<ZV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<ZV&>().size()), unsigned int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<ZV const&>().size()), unsigned int>::value, "");
	}

	// (sized_range<Views> && ...) && !(sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<int, void>;
		using V2 = TestSizedView<int, short>;
		static_assert( hamon::ranges::sized_range_t<V1>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V1 const>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2 const>::value, "");

		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert( has_size<ZV&>::value, "");
		static_assert(!has_size<ZV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<ZV&>().size()), unsigned int>::value, "");
	}
	
	// !(sized_range<Views> && ...) && !(sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<void, short>;
		using V2 = TestSizedView<int, void>;
		static_assert(!hamon::ranges::sized_range_t<V1>::value, "");
		static_assert( hamon::ranges::sized_range_t<V2>::value, "");
		static_assert( hamon::ranges::sized_range_t<V1 const>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V2 const>::value, "");

		using ZV = hamon::ranges::zip_view<V1, V2>;
		static_assert(!has_size<ZV&>::value, "");
		static_assert(!has_size<ZV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<int>;
	using ZV = hamon::ranges::zip_view<V1, V2>;

	{
		int a1[] = {1, 2, 3};
		int a2[] = {1, 2, 3};
		V1 v1(a1);
		V2 v2(a2);
		{
			ZV zv {v1, v2};
			VERIFY(zv.size() == 3);
		}
		{
			ZV const zv {v1, v2};
			VERIFY(zv.size() == 3);
		}
	}
	{
		int a1[] = {1, 2, 3, 4};
		int a2[] = {1, 2, 3, 4, 5};
		V1 v1(a1);
		V2 v2(a2);
		{
			ZV zv {v1, v2};
			VERIFY(zv.size() == 4);
		}
		{
			ZV const zv {v1, v2};
			VERIFY(zv.size() == 4);
		}
	}
	{
		int a1[] = {1, 2, 3, 4};
		int a2[] = {1, 2};
		V1 v1(a1);
		V2 v2(a2);
		{
			ZV zv {v1, v2};
			VERIFY(zv.size() == 2);
		}
		{
			ZV const zv {v1, v2};
			VERIFY(zv.size() == 2);
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace size_test
}	// namespace zip_view_test
}	// namespace hamon_ranges_test
