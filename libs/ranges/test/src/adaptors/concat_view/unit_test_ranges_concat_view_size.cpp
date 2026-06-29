/**
 *	@file	unit_test_ranges_concat_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires (sized_range<Views> && ...);
 *	constexpr auto size() const requires (sized_range<const Views> && ...);
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/iterator/detail/is_unsigned_integer_like.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	//  (sized_range<Views> && ...) &&
	//  (sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<int, short>;
		using V2 = TestSizedView<char, short>;
		static_assert( hamon::ranges::sized_range<V1>, "");
		static_assert( hamon::ranges::sized_range<V2>, "");
		static_assert( hamon::ranges::sized_range<V1 const>, "");
		static_assert( hamon::ranges::sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_size<CV&>::value, "");
		static_assert( has_size<CV const&>::value, "");

		using D  = decltype(hamon::declval<CV&>().size());
		using CD = decltype(hamon::declval<CV const&>().size());
		static_assert(hamon::detail::is_unsigned_integer_like<D>, "");
		static_assert(hamon::detail::is_unsigned_integer_like<CD>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	//  (sized_range<Views> && ...) &&
	// !(sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<char, short>;
		using V2 = TestSizedView<char, void>;
		static_assert( hamon::ranges::sized_range<V1>, "");
		static_assert( hamon::ranges::sized_range<V2>, "");
		static_assert( hamon::ranges::sized_range<V1 const>, "");
		static_assert(!hamon::ranges::sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");

		using D = decltype(hamon::declval<CV&>().size());
		static_assert(hamon::detail::is_unsigned_integer_like<D>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// !(sized_range<Views> && ...) &&
	//  (sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<void, short>;
		using V2 = TestSizedView<char, int>;
		static_assert(!hamon::ranges::sized_range<V1>, "");
		static_assert( hamon::ranges::sized_range<V2>, "");
		static_assert( hamon::ranges::sized_range<V1 const>, "");
		static_assert( hamon::ranges::sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert( has_size<CV&>::value, "");
		static_assert( has_size<CV const&>::value, "");

		using D  = decltype(hamon::declval<CV&>().size());
		using CD = decltype(hamon::declval<CV const&>().size());
		static_assert(hamon::detail::is_unsigned_integer_like<D>, "");
		static_assert(hamon::detail::is_unsigned_integer_like<CD>, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// !(sized_range<Views> && ...) &&
	// !(sized_range<const Views> && ...)
	{
		using V1 = TestSizedView<void, short>;
		using V2 = TestSizedView<char, void>;
		static_assert(!hamon::ranges::sized_range<V1>, "");
		static_assert( hamon::ranges::sized_range<V2>, "");
		static_assert( hamon::ranges::sized_range<V1 const>, "");
		static_assert(!hamon::ranges::sized_range<V2 const>, "");

		using CV = hamon::ranges::concat_view<V1, V2>;
		static_assert(!has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	using V1 = test_random_access_view<int>;
	using V2 = test_random_access_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;

	{
		int a1[] = {1, 2};
		int a2[] = {1, 2, 3};
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv {v1, v2};
			VERIFY(cv.size() == 5);
		}
		{
			CV const cv {v1, v2};
			VERIFY(cv.size() == 5);
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	using V1 = test_input_sized_view<int>;
	using V2 = test_input_sized_view<int>;
	using CV = hamon::ranges::concat_view<V1, V2>;

	{
		int a1[] = {3, 1, 4, 1, 5};
		int a2[] = {1, 2, 3};
		V1 v1(a1);
		V2 v2(a2);
		{
			CV cv {v1, v2};
			VERIFY(cv.size() == 8);
		}
		{
			CV const cv {v1, v2};
			VERIFY(cv.size() == 8);
		}
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test06()
{
	auto a = { 1, 2 };
	auto b = { 1, 2, 3 };
	auto c = { 1, 2, 3, 4 };

	auto con{ hamon::views::concat(a, b, c) };
	static_assert(hamon::ranges::sized_range<decltype(con)>, "");
	VERIFY(con.size() == 2 + 3 + 4);

	hamon::forward_list<int> d = b;
	static_assert(!hamon::ranges::sized_range<hamon::forward_list<int>>, "");
	const auto cat{ hamon::views::concat(b, c, d) };
	static_assert(!hamon::ranges::sized_range<decltype(cat)>, "");
	// auto x = cat.size(); // error: cat is not sized_range because of d

	hamon::list<int> e = c;
	const auto dog{ hamon::views::concat(a, b, e) };
	static_assert(hamon::ranges::sized_range<decltype(dog)>, "");
	VERIFY(dog.size() == 2 + 3 + 4);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace size_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
