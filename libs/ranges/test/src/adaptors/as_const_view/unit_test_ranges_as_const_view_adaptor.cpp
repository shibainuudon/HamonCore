/**
 *	@file	unit_test_ranges_as_const_view_adaptor.cpp
 *
 *	@brief	views::as_const のテスト
 *
 *	namespace views { inline constexpr unspecified as_const = unspecified; }
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/span.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_const_view_test
{
namespace adaptor_test
{

template <typename T, typename Iterator, typename Sentinel, typename ConstIterator, typename ConstSentinel>
struct TestRange
{
	T* m_first;
	T* m_last;

	HAMON_CXX11_CONSTEXPR TestRange() : m_first(nullptr), m_last(nullptr) {}

	template <hamon::size_t N>
	explicit HAMON_CXX11_CONSTEXPR TestRange(T (&arr)[N]) : TestRange(arr, arr+N) {}

	HAMON_CXX11_CONSTEXPR TestRange(T* first, T* last) : m_first(first), m_last(last) {}

	HAMON_CXX14_CONSTEXPR Iterator      begin()       noexcept { return Iterator{m_first}; }
	HAMON_CXX11_CONSTEXPR ConstIterator begin() const noexcept { return ConstIterator{m_first}; }
	HAMON_CXX14_CONSTEXPR Sentinel      end()         noexcept { return Sentinel{m_last}; }
	HAMON_CXX11_CONSTEXPR ConstSentinel end()   const noexcept { return ConstSentinel{m_last}; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	// [range.as.const.overview]/2.1
	// V is a constant_range

	using V = test_input_view<int const>;
	//static_assert(hamon::ranges::constant_range_t<hamon::views::all_t<V>>::value, "");

	using CV = hamon::views::all_t<V>;

	int a[] = {1,2,3};
	V v(a);

	// views::as_const(v)
	{
		auto cv = hamon::views::as_const(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}
	// v | views::as_const
	{
		auto cv = v | hamon::views::as_const;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	// [range.as.const.overview]/2.2
	// V is an empty_view

	using V = hamon::ranges::empty_view<int>;
	//static_assert(!hamon::ranges::constant_range_t<hamon::views::all_t<V>>::value, "");
	//static_assert( hamon::detail::is_specialization_of_empty_view<V>::value, "");

	using CV = hamon::ranges::empty_view<int const>;

	V v{};

	// views::as_const(v)
	{
		auto cv = hamon::views::as_const(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::empty(cv));
	}
	// v | views::as_const
	{
		auto cv = v | hamon::views::as_const;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::empty(cv));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// [range.as.const.overview]/2.3
	// V is a span

	using V = hamon::span<int>;
	//static_assert(!hamon::ranges::constant_range_t<hamon::views::all_t<V>>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_empty_view<V>::value, "");
	//static_assert( hamon::detail::is_specialization_of_span<V>::value, "");

	using CV = hamon::span<int const>;

	int a[] = {1,2,3,4};
	V v(a, a+4);

	// views::as_const(v)
	{
		auto cv = hamon::views::as_const(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}
	// v | views::as_const
	{
		auto cv = v | hamon::views::as_const;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// [range.as.const.overview]/2.4
	// V is a ref_view

	using R = TestRange<int,
		input_iterator_wrapper<int>,
		input_iterator_wrapper<int>,
		input_iterator_wrapper<int const>,
		input_iterator_wrapper<int const>>;
	using V = hamon::ranges::ref_view<R>;
	//static_assert(!hamon::ranges::constant_range_t<hamon::views::all_t<V>>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_empty_view<V>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_span<V>::value, "");
	//static_assert( hamon::ranges::views::detail::is_specialization_of_ref_view<V>::value, "");
	//static_assert( hamon::ranges::constant_range_t<R const>::value, "");

	using CV = hamon::ranges::ref_view<R const>;

	int a[] = {1, 2};
	R r(a);
	V v(r);

	// views::as_const(v)
	{
		auto cv = hamon::views::as_const(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}
	// v | views::as_const
	{
		auto cv = v | hamon::views::as_const;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// [range.as.const.overview]/2.5
	// V is an lvalue, constant_range, and not view

	using V = TestRange<int,
		input_iterator_wrapper<int>,
		input_iterator_wrapper<int>,
		input_iterator_wrapper<int const>,
		input_iterator_wrapper<int const>>;
	//static_assert(!hamon::ranges::constant_range_t<hamon::views::all_t<V>>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_empty_view<V>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_span<V>::value, "");
	//static_assert(!hamon::ranges::views::detail::is_specialization_of_ref_view<V>::value, "");
	//static_assert( hamon::ranges::constant_range_t<V const>::value, "");
	//static_assert(!hamon::ranges::view_t<V>::value, "");

	using CV = hamon::ranges::ref_view<V const>;

	int a[] = {3,1,4,1,5,9};
	V v(a);

	// views::as_const(v)
	{
		auto cv = hamon::views::as_const(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}
	// v | views::as_const
	{
		auto cv = v | hamon::views::as_const;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	// [range.as.const.overview]/2.6
	// Otherwise

	using V = test_input_range<int>;

	//static_assert(!hamon::ranges::constant_range_t<hamon::views::all_t<V>>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_empty_view<V>::value, "");
	//static_assert(!hamon::detail::is_specialization_of_span<V>::value, "");
	//static_assert(!hamon::ranges::views::detail::is_specialization_of_ref_view<V>::value, "");
	//static_assert(!hamon::ranges::constant_range_t<V const>::value, "");

	using CV = hamon::ranges::as_const_view<hamon::views::all_t<V&>>;

	int a[] = {1,2,3,4,5};
	V v(a);

	// views::as_const(v)
	{
		auto cv = hamon::views::as_const(v);
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}
	// v | views::as_const
	{
		auto cv = v | hamon::views::as_const;
		static_assert(hamon::is_same<decltype(cv), CV>::value, "");
		static_assert(hamon::ranges::constant_range_t<decltype(cv)>::value, "");
		VERIFY(hamon::ranges::equal(cv, a));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsConstViewAdaptorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace adaptor_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
