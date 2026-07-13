/**
 *	@file	unit_test_ranges_single_view.cpp
 *
 *	@brief	ranges::single_view のテスト
 */

#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace single_view_test
{

struct Copyable
{
	Copyable();
	Copyable(Copyable const&);
};

struct Movable
{
	Movable();
	Movable(Movable const&) = delete;
	Movable(Movable &&);
};

struct NonMovable
{
	NonMovable();
	NonMovable(NonMovable const&) = delete;
	NonMovable(NonMovable &&)     = delete;
};

struct NonDefaultConstructible
{
	NonDefaultConstructible() = delete;
};

template <typename T, typename = void>
struct CanInstantiateSingleView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateSingleView<T, hamon::void_t<hamon::ranges::single_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateSingleView<int>::value, "");
static_assert( CanInstantiateSingleView<float>::value, "");
static_assert( CanInstantiateSingleView<Copyable>::value, "");
static_assert( CanInstantiateSingleView<Movable>::value, "");
static_assert(!CanInstantiateSingleView<NonMovable>::value, "");
static_assert( CanInstantiateSingleView<NonDefaultConstructible>::value, "");
static_assert(!CanInstantiateSingleView<void>::value, "");

static_assert( hamon::is_default_constructible<hamon::ranges::single_view<int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::single_view<Copyable>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::single_view<NonDefaultConstructible>>::value, "");

static_assert( hamon::is_constructible<hamon::ranges::single_view<int>,      int const&>::value, "");
static_assert( hamon::is_constructible<hamon::ranges::single_view<Copyable>, Copyable const&>::value, "");
static_assert(!hamon::is_constructible<hamon::ranges::single_view<Movable>,  Movable const&>::value, "");

static_assert( hamon::is_constructible<hamon::ranges::single_view<int>,      int&&>::value, "");
static_assert( hamon::is_constructible<hamon::ranges::single_view<Copyable>, Copyable&&>::value, "");
static_assert( hamon::is_constructible<hamon::ranges::single_view<Movable>,  Movable&&>::value, "");

static_assert( hamon::is_constructible<hamon::ranges::single_view<int>,      hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::ranges::single_view<Copyable>, hamon::in_place_t, int>::value, "");
static_assert(!hamon::is_constructible<hamon::ranges::single_view<Movable>,  hamon::in_place_t, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	using T = int;
	using SV = hamon::ranges::single_view<T>;
	using CSV = SV const;

	T const n = 4;
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::single_view sv{n};
	static_assert(hamon::is_same<decltype(sv), SV>::value, "");
#else
	SV sv{n};
#endif
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(sv)>, T>::value, "");

	static_assert( hamon::ranges::range_t<SV>::value, "");
	static_assert(!hamon::ranges::borrowed_range_t<SV>::value, "");
	static_assert( hamon::ranges::sized_range_t<SV>::value, "");
	static_assert( hamon::ranges::approximately_sized_range<SV>, "");
	static_assert( hamon::ranges::output_range_t<SV, T>::value, "");
	static_assert( hamon::ranges::input_range_t<SV>::value, "");
	static_assert( hamon::ranges::forward_range_t<SV>::value, "");
	static_assert( hamon::ranges::bidirectional_range_t<SV>::value, "");
	static_assert( hamon::ranges::random_access_range_t<SV>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<SV>::value, "");
	static_assert( hamon::ranges::common_range_t<SV>::value, "");
	static_assert( hamon::ranges::viewable_range_t<SV>::value, "");
	static_assert( hamon::ranges::view_t<SV>::value, "");
	static_assert(!hamon::ranges::constant_range_t<SV>::value, "");

	static_assert( hamon::ranges::range_t<CSV>::value, "");
	static_assert(!hamon::ranges::borrowed_range_t<CSV>::value, "");
	static_assert( hamon::ranges::sized_range_t<CSV>::value, "");
	static_assert( hamon::ranges::approximately_sized_range<CSV>, "");
	static_assert(!hamon::ranges::output_range_t<CSV, T>::value, "");
	static_assert( hamon::ranges::input_range_t<CSV>::value, "");
	static_assert( hamon::ranges::forward_range_t<CSV>::value, "");
	static_assert( hamon::ranges::bidirectional_range_t<CSV>::value, "");
	static_assert( hamon::ranges::random_access_range_t<CSV>::value, "");
	static_assert( hamon::ranges::contiguous_range_t<CSV>::value, "");
	static_assert( hamon::ranges::common_range_t<CSV>::value, "");
	static_assert( hamon::ranges::viewable_range_t<CSV>::value, "");
	static_assert(!hamon::ranges::view_t<CSV>::value, "");
	static_assert( hamon::ranges::constant_range_t<CSV>::value, "");

	static_assert( has_begin<SV>::value, "");
	static_assert( has_end<SV>::value, "");
	static_assert( has_empty<SV>::value, "");
	static_assert( has_cbegin<SV>::value, "");
	static_assert( has_cend<SV>::value, "");
	static_assert( has_operator_bool<SV>::value, "");
	static_assert( has_data<SV>::value, "");
	static_assert( has_size<SV>::value, "");
	static_assert( has_front<SV>::value, "");
	static_assert( has_back<SV>::value, "");
	static_assert( has_subscript<SV>::value, "");

	static_assert( has_begin<CSV>::value, "");
	static_assert( has_end<CSV>::value, "");
	static_assert( has_empty<CSV>::value, "");
	static_assert( has_cbegin<CSV>::value, "");
	static_assert( has_cend<CSV>::value, "");
	static_assert( has_operator_bool<CSV>::value, "");
	static_assert( has_data<CSV>::value, "");
	static_assert( has_size<CSV>::value, "");
	static_assert( has_front<CSV>::value, "");
	static_assert( has_back<CSV>::value, "");
	static_assert( has_subscript<CSV>::value, "");

	VERIFY(sv.empty()  == false);
	VERIFY(sv.size()   == 1);
	VERIFY(sv.begin()  != sv.end());
	VERIFY(sv.cbegin() != sv.cend());
	VERIFY(*sv.data()  == n);
	VERIFY((bool)sv    == true);
	VERIFY(sv.front()  == n);
	VERIFY(sv.back()   == n);
	VERIFY(sv[0]       == n);

	VERIFY(hamon::ranges::size(sv) == 1);
	VERIFY(!hamon::ranges::empty(sv));

	CSV csv{n};

	VERIFY(csv.empty()  == false);
	VERIFY(csv.size()   == 1);
	VERIFY(csv.begin()  != csv.end());
	VERIFY(csv.cbegin() != csv.cend());
	VERIFY(*csv.data()  == n);
	VERIFY((bool)csv    == true);
	VERIFY(csv.front()  == n);
	VERIFY(csv.back()   == n);
	VERIFY(csv[0]       == n);

	VERIFY(hamon::ranges::size(csv) == 1);
	VERIFY(!hamon::ranges::empty(csv));

	int count = 0;
	for (auto i : sv)
	{
		VERIFY(i == n);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*hamon::ranges::begin(sv) == n);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	hamon::ranges::single_view<long> const sv {};
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(sv)>, long>::value, "");
	VERIFY(hamon::ranges::size(sv) == 1);

	VERIFY(sv.empty() == false);
	VERIFY(sv.size() == 1);

	int count = 0;
	for (auto l : sv)
	{
		VERIFY(l == 0L);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*hamon::ranges::begin(sv) == 0L);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	hamon::ranges::single_view<float> sv(hamon::in_place, 0.5f);
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(sv)>, float>::value, "");
	VERIFY(hamon::ranges::size(sv) == 1);

	VERIFY(sv.empty() == false);
	VERIFY(sv.size() == 1);

	int count = 0;
	for (auto l : sv)
	{
		VERIFY(l == 0.5f);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*hamon::ranges::begin(sv) == 0.5f);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	auto sv = hamon::views::single('a');
	static_assert(hamon::is_same<hamon::ranges::range_value_t<decltype(sv)>, char>::value, "");
	VERIFY(hamon::ranges::size(sv) == 1);
	VERIFY(*hamon::ranges::begin(sv) == 'a');

	VERIFY(sv.empty() == false);
	VERIFY(sv.size() == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SingleViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace single_view_test
}	// namespace hamon_ranges_test
