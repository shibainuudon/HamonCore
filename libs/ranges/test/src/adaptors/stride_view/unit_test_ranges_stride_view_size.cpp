/**
 *	@file	unit_test_ranges_stride_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires sized_range<V>;
 *	constexpr auto size() const requires sized_range<const V>;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace size_test
{

template <typename D1, typename D2, typename Iterator>
struct TestSizedView : hamon::ranges::view_base
{
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

template <typename Iterator>
HAMON_CXX14_CONSTEXPR bool test00()
{
	// sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<int, short, Iterator>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_size<SV&>::value, "");
		static_assert( has_size<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().size()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<SV const&>().size()), hamon::uintptr_t>::value, "");
	}

	// !sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<void, unsigned int, Iterator>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_size<SV&>::value, "");
		static_assert( has_size<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().size()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<SV const&>().size()), hamon::uintptr_t>::value, "");
	}

	// sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<long, void, Iterator>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert( has_size<SV&>::value, "");
		static_assert(!has_size<SV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<SV&>().size()), hamon::uintptr_t>::value, "");
	}

	// !sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<void, void, Iterator>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using SV = hamon::ranges::stride_view<V>;
		static_assert(!has_size<SV&>::value, "");
		static_assert(!has_size<SV const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V = test_random_access_view<int>;
	using SV = hamon::ranges::stride_view<V>;

	int a[] = {0,1,2,3,4};
	V v(a);

	{
		SV sv(v, 1);
		SV const& csv = sv;
		VERIFY(sv.size()  == 5);
		VERIFY(csv.size() == 5);
	}
	{
		SV sv(v, 2);
		SV const& csv = sv;
		VERIFY(sv.size()  == 3);
		VERIFY(csv.size() == 3);
	}
	{
		SV sv(v, 3);
		SV const& csv = sv;
		VERIFY(sv.size()  == 2);
		VERIFY(csv.size() == 2);
	}
	{
		SV sv(v, 4);
		SV const& csv = sv;
		VERIFY(sv.size()  == 2);
		VERIFY(csv.size() == 2);
	}
	{
		SV sv(v, 5);
		SV const& csv = sv;
		VERIFY(sv.size()  == 1);
		VERIFY(csv.size() == 1);
	}
	{
		SV sv(v, 6);
		SV const& csv = sv;
		VERIFY(sv.size()  == 1);
		VERIFY(csv.size() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<input_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<forward_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace size_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
