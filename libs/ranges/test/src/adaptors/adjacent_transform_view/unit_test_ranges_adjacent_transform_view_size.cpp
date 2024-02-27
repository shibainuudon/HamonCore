/**
 *	@file	unit_test_ranges_adjacent_transform_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires sized_range<InnerView>;
 *	constexpr auto size() const requires sized_range<const InnerView>;
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
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
namespace adjacent_transform_view_test
{
namespace size_test
{

struct F
{
	HAMON_CXX11_CONSTEXPR int operator()(int x) const { return x; }
	HAMON_CXX11_CONSTEXPR int operator()(int x, int y) const { return x + y; }
	HAMON_CXX11_CONSTEXPR int operator()(int x, int y, int z) const { return x + y + z; }
	HAMON_CXX11_CONSTEXPR int operator()(int x, int y, int z, int w) const { return x + y + z + w; }
	HAMON_CXX11_CONSTEXPR int operator()(int x, int y, int z, int w, int s) const { return x + y + z + w + s; }
};

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
	// sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<int, short>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( has_size<AV&>::value, "");
		static_assert( has_size<AV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<AV&>().size()), int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<AV const&>().size()), short>::value, "");
	}

	// !sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<void, unsigned int>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( has_size<AV&>::value, "");
		static_assert( has_size<AV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<AV&>().size()), unsigned int>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<AV const&>().size()), unsigned int>::value, "");
	}

	// sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<long, void>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert( has_size<AV&>::value, "");
		static_assert(!has_size<AV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<AV&>().size()), long>::value, "");
	}

	// !sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<void, void>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		static_assert(!has_size<AV&>::value, "");
		static_assert(!has_size<AV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1,2,3,4};

	using V = test_random_access_view<int>;
	V v(a);
	F f;
	{
		using AV = hamon::ranges::adjacent_transform_view<V, F, 1>;
		{
			AV av {v, f};
			VERIFY(av.size() == 4);
		}
		{
			AV const av {v, f};
			VERIFY(av.size() == 4);
		}
	}
	{
		using AV = hamon::ranges::adjacent_transform_view<V, F, 2>;
		{
			AV av {v, f};
			VERIFY(av.size() == 3);
		}
		{
			AV const av {v, f};
			VERIFY(av.size() == 3);
		}
	}
	{
		using AV = hamon::ranges::adjacent_transform_view<V, F, 3>;
		{
			AV av {v, f};
			VERIFY(av.size() == 2);
		}
		{
			AV const av {v, f};
			VERIFY(av.size() == 2);
		}
	}
	{
		using AV = hamon::ranges::adjacent_transform_view<V, F, 4>;
		{
			AV av {v, f};
			VERIFY(av.size() == 1);
		}
		{
			AV const av {v, f};
			VERIFY(av.size() == 1);
		}
	}
	{
		using AV = hamon::ranges::adjacent_transform_view<V, F, 5>;
		{
			AV av {v, f};
			VERIFY(av.size() == 0);
		}
		{
			AV const av {v, f};
			VERIFY(av.size() == 0);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace size_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
