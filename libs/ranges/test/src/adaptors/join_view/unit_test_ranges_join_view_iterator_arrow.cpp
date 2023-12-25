/**
 *	@file	unit_test_ranges_join_view_iterator_arrow.cpp
 *
 *	@brief	operator->のテスト
 *
 *	constexpr InnerIter operator->() const;
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/array.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_arrow_test
{

template <typename T>
struct ArrowInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR ArrowInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                  operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T*                  operator->() const { return m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ArrowInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ArrowInputIterator& rhs) const { return !(*this == rhs); }
};
static_assert(hamon::copyable_t<ArrowInputIterator<int>>::value, "");

template <typename T>
struct MoveOnlyArrowInputIterator
{
	T*	m_ptr = nullptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	MoveOnlyArrowInputIterator() = default;
	MoveOnlyArrowInputIterator(MoveOnlyArrowInputIterator&&) = default;
	MoveOnlyArrowInputIterator& operator=(MoveOnlyArrowInputIterator&&) = default;
	HAMON_CXX14_CONSTEXPR MoveOnlyArrowInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                        operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                          operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T*                          operator->() const { return m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const MoveOnlyArrowInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const MoveOnlyArrowInputIterator& rhs) const { return !(*this == rhs); }
};
static_assert(!hamon::copyable_t<MoveOnlyArrowInputIterator<int>>::value, "");
static_assert( hamon::input_iterator_t<MoveOnlyArrowInputIterator<int>>::value, "");

struct MoveOnlyIterInnerView : hamon::ranges::view_base
{
	using iterator = MoveOnlyArrowInputIterator<int>;
	using sentinel = hamon::unreachable_sentinel_t;
	
	iterator begin() const { return iterator{}; }
	sentinel end() const { return sentinel{}; }
};

template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int a[2][3] =
	{
		{1, 2, 3},
		{4, 5, 6},
	};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_view rv(a);
	static_assert(hamon::is_same<decltype(rv), hamon::ranges::join_view<hamon::ranges::ref_view<int[2][3]>>>::value, "");
#else
	hamon::ranges::join_view<hamon::ranges::ref_view<int[2][3]>> rv(a);
#endif
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(it.operator->()), int*>::value, "");
	VERIFY(it.operator->() == &a[0][0]);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2][3] =
	{
		{1, 2, 3},
		{4, 5, 6},
	};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_view rv(a);
	static_assert(hamon::is_same<decltype(rv), hamon::ranges::join_view<hamon::ranges::ref_view<int const[2][3]>>>::value, "");
#else
	hamon::ranges::join_view<hamon::ranges::ref_view<int const[2][3]>> rv(a);
#endif
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(it.operator->()), int const*>::value, "");
	VERIFY(it.operator->() == &a[0][0]);
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	{
		using V = test_random_access_view<test_random_access_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_arrow<I>::value, "");
	}
	{
		using V = test_contiguous_view<test_random_access_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_arrow<I>::value, "");
	}
	{
		using V = test_random_access_view<test_contiguous_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert( has_arrow<I>::value, "");
		I it{};
		static_assert(hamon::is_same<decltype(it.operator->()), contiguous_iterator_wrapper<int>>::value, "");
	}
	{
		using V = test_input_view<test_view<int, ArrowInputIterator<int>>>;
		using RV = hamon::ranges::join_view<V>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert( has_arrow<I>::value, "");
	}
	{
		using V = hamon::ranges::ref_view<MoveOnlyIterInnerView[2]>;
		using RV = hamon::ranges::join_view<V>;
		using I = hamon::ranges::iterator_t<RV>;
		static_assert(!has_arrow<I>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	hamon::array<hamon::string_view, 5> a = {{{}, "Hello ", {}, "World!", {}}};
	auto rv = a | hamon::views::join;
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(it.operator->()), typename hamon::string_view::iterator>::value, "");
	VERIFY(*(it.operator->()) == 'H');
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorArrowTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test00());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace iterator_arrow_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
