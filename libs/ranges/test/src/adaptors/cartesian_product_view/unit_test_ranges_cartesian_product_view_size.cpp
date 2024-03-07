/**
 *	@file	unit_test_ranges_cartesian_product_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr see below size()
 *	  requires cartesian-product-is-sized<First, Vs...>;
 *
 *	constexpr see below size() const
 *	  requires cartesian-product-is-sized<const First, const Vs...>;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/iterator/detail/is_unsigned_integer_like.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
//#include <hamon/tuple.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
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
	// cartesian_product_is_sized<Views...> && cartesian_product_is_sized<Views const...>
	{
		using V1 = TestSizedView<int, short>;
		using V2 = TestSizedView<char, short>;
		//static_assert( hamon::ranges::cartesian_product_is_sized<V1, V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_sized<V1 const, V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_size<CV&>::value, "");
		static_assert( has_size<CV const&>::value, "");

		using D  = decltype(hamon::declval<CV&>().size());
		using CD = decltype(hamon::declval<CV const&>().size());
		static_assert(hamon::detail::is_unsigned_integer_like_t<D>::value, "");
		static_assert(hamon::detail::is_unsigned_integer_like_t<CD>::value, "");
	}

	// cartesian_product_is_sized<Views...> && !cartesian_product_is_sized<Views const...>
	{
		using V1 = TestSizedView<int, void>;
		using V2 = TestSizedView<char, short>;
		//static_assert( hamon::ranges::cartesian_product_is_sized<V1, V2>, "");
		//static_assert(!hamon::ranges::cartesian_product_is_sized<V1 const, V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");

		using D  = decltype(hamon::declval<CV&>().size());
		static_assert(hamon::detail::is_unsigned_integer_like_t<D>::value, "");
	}

	// !cartesian_product_is_sized<Views...> && cartesian_product_is_sized<Views const...>
	{
		using V1 = TestSizedView<void, int>;
		using V2 = TestSizedView<char, short>;
		//static_assert(!hamon::ranges::cartesian_product_is_sized<V1, V2>, "");
		//static_assert( hamon::ranges::cartesian_product_is_sized<V1 const, V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert( has_size<CV&>::value, "");
		static_assert( has_size<CV const&>::value, "");
	
		using D  = decltype(hamon::declval<CV&>().size());
		using CD = decltype(hamon::declval<CV const&>().size());
		static_assert(hamon::detail::is_unsigned_integer_like_t<D>::value, "");
		static_assert(hamon::detail::is_unsigned_integer_like_t<CD>::value, "");
}

	// !cartesian_product_is_sized<Views...> && !cartesian_product_is_sized<Views const...>
	{
		using V1 = TestSizedView<void, void>;
		using V2 = TestSizedView<char, short>;
		//static_assert(!hamon::ranges::cartesian_product_is_sized<V1, V2>, "");
		//static_assert(!hamon::ranges::cartesian_product_is_sized<V1 const, V2 const>, "");

		using CV = hamon::ranges::cartesian_product_view<V1, V2>;
		static_assert(!has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<int>;
	using CV = hamon::ranges::cartesian_product_view<V1, V2>;

	{
		int a1[] = {1, 2};
		int a2[] = {1, 2, 3};
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv {v1, v1};
			VERIFY(cv.size() == 4);
		}
		{
			CV const cv {v2, v2};
			VERIFY(cv.size() == 9);
		}
		{
			CV cv {v1, v2};
			VERIFY(cv.size() == 6);
		}
		{
			CV const cv {v1, v2};
			VERIFY(cv.size() == 6);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<char>;
	using V3 = test_random_access_view<float>;
	using CV = hamon::ranges::cartesian_product_view<V1, V2, V3>;

	int a1[] = {1,2,3};
	char a2[] = {'a', 'b'};
	float a3[] = {0.5f, 1.5f, 2.5f};
	V1 v1(a1);
	V2 v2(a2);
	V3 v3(a3);
	{
		CV cv(v1, v2, v3);
		VERIFY(cv.size() == 18);
	}
	{
		CV const cv(v1, v2, v3);
		VERIFY(cv.size() == 18);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());

	{
		int a[] = {1,2,3};
		hamon::vector<int> v;
		{
			auto cv = hamon::views::cartesian_product(a, v);
			EXPECT_EQ(0u, cv.size());
		}
		v.push_back(4);
		{
			auto cv = hamon::views::cartesian_product(a, v);
			EXPECT_EQ(3u, cv.size());
		}
		v.push_back(5);
		{
			auto cv = hamon::views::cartesian_product(a, v);
			EXPECT_EQ(6u, cv.size());
		}
	}
}

}	// namespace size_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
