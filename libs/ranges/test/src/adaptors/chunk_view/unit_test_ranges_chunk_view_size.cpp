/**
 *	@file	unit_test_ranges_chunk_view_size.cpp
 *
 *	@brief	size() のテスト
 *
 *	constexpr auto size() requires sized_range<V>;
 *	constexpr auto size() const requires sized_range<const V>;
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
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
namespace chunk_view_test
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

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_size<CV&>::value, "");
		static_assert( has_size<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().size()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().size()), hamon::uintptr_t>::value, "");
	}

	// !sized_range<V> && sized_range<V const>
	{
		using V = TestSizedView<void, unsigned int, Iterator>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert( hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_size<CV&>::value, "");
		static_assert( has_size<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().size()), hamon::uintptr_t>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<CV const&>().size()), hamon::uintptr_t>::value, "");
	}

	// sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<long, void, Iterator>;
		static_assert( hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert( has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");

		static_assert(hamon::is_same<decltype(hamon::declval<CV&>().size()), hamon::uintptr_t>::value, "");
	}

	// !sized_range<V> && !sized_range<V const>
	{
		using V = TestSizedView<void, void, Iterator>;
		static_assert(!hamon::ranges::sized_range_t<V>::value, "");
		static_assert(!hamon::ranges::sized_range_t<V const>::value, "");

		using CV = hamon::ranges::chunk_view<V>;
		static_assert(!has_size<CV&>::value, "");
		static_assert(!has_size<CV const&>::value, "");
	}
	return true;
}

template <template <typename> class View>
HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {0,1,2,3,4,5,6,7,8,9};

	using V = View<int>;
	V v(a);

	using CV = hamon::ranges::chunk_view<V>;
	{
		CV cv{v, 1};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 10);
		VERIFY(ccv.size() == 10);
	}
	{
		CV cv{v, 2};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 5);
		VERIFY(ccv.size() == 5);
	}
	{
		CV cv{v, 3};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 4);
		VERIFY(ccv.size() == 4);
	}
	{
		CV cv{v, 4};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 3);
		VERIFY(ccv.size() == 3);
	}
	{
		CV cv{v, 5};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 2);
		VERIFY(ccv.size() == 2);
	}
	{
		CV cv{v, 6};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 2);
		VERIFY(ccv.size() == 2);
	}
	{
		CV cv{v, 9};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 2);
		VERIFY(ccv.size() == 2);
	}
	{
		CV cv{v, 10};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 1);
		VERIFY(ccv.size() == 1);
	}
	{
		CV cv{v, 11};
		CV const& ccv = cv;
		VERIFY(cv.size()  == 1);
		VERIFY(ccv.size() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<input_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<forward_iterator_wrapper<int>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_input_sized_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<test_forward_sized_view>());
}

}	// namespace size_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
