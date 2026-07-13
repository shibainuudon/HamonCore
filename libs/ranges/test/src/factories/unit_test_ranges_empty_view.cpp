/**
 *	@file	unit_test_ranges_empty_view.cpp
 *
 *	@brief	ranges::empty_view のテスト
 */

#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/cbegin.hpp>
#include <hamon/ranges/cend.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace empty_view_test
{

struct Copyable
{
	Copyable(Copyable const&);
};

struct Movable
{
	Movable(Movable const&) = delete;
	Movable(Movable &&);
};

struct NonMovable
{
	NonMovable(NonMovable const&) = delete;
	NonMovable(NonMovable &&)     = delete;
};

template <typename T, typename = void>
struct CanInstantiateEmptyView
	: hamon::false_type {};

template <typename T>
struct CanInstantiateEmptyView<T, hamon::void_t<hamon::ranges::empty_view<T>>>
	: hamon::true_type {};

static_assert( CanInstantiateEmptyView<int>::value, "");
static_assert( CanInstantiateEmptyView<float>::value, "");
static_assert( CanInstantiateEmptyView<Copyable>::value, "");
static_assert( CanInstantiateEmptyView<Movable>::value, "");
static_assert( CanInstantiateEmptyView<NonMovable>::value, "");
static_assert(!CanInstantiateEmptyView<void>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	using EV = hamon::ranges::empty_view<T>;
	using CEV = EV const;

	static_assert( hamon::ranges::range_t<EV>::value, "");
	static_assert( hamon::ranges::borrowed_range<EV>, "");
	static_assert( hamon::ranges::sized_range_t<EV>::value, "");
	static_assert( hamon::ranges::approximately_sized_range<EV>, "");
	static_assert( hamon::ranges::output_range<EV, T>, "");
	static_assert( hamon::ranges::input_range<EV>, "");
	static_assert( hamon::ranges::forward_range<EV>, "");
	static_assert( hamon::ranges::bidirectional_range<EV>, "");
	static_assert( hamon::ranges::random_access_range_t<EV>::value, "");
	static_assert( hamon::ranges::contiguous_range<EV>, "");
	static_assert( hamon::ranges::common_range<EV>, "");
	static_assert( hamon::ranges::viewable_range_t<EV>::value, "");
	static_assert( hamon::ranges::view_t<EV>::value, "");
	static_assert(!hamon::ranges::constant_range<EV>, "");

	static_assert( hamon::ranges::range_t<CEV>::value, "");
	static_assert( hamon::ranges::borrowed_range<CEV>, "");
	static_assert( hamon::ranges::sized_range_t<CEV>::value, "");
	static_assert( hamon::ranges::approximately_sized_range<CEV>, "");
	static_assert( hamon::ranges::output_range<CEV, T>, "");
	static_assert( hamon::ranges::input_range<CEV>, "");
	static_assert( hamon::ranges::forward_range<CEV>, "");
	static_assert( hamon::ranges::bidirectional_range<CEV>, "");
	static_assert( hamon::ranges::random_access_range_t<CEV>::value, "");
	static_assert( hamon::ranges::contiguous_range<CEV>, "");
	static_assert( hamon::ranges::common_range<CEV>, "");
	static_assert( hamon::ranges::viewable_range_t<CEV>::value, "");
	static_assert(!hamon::ranges::view_t<CEV>::value, "");
	static_assert(!hamon::ranges::constant_range<CEV>, "");

	static_assert( has_begin<EV>::value, "");
	static_assert( has_end<EV>::value, "");
	static_assert( has_empty<EV>::value, "");
	static_assert( has_cbegin<EV>::value, "");
	static_assert( has_cend<EV>::value, "");
	static_assert( has_operator_bool<EV>::value, "");
	static_assert( has_data<EV>::value, "");
	static_assert( has_size<EV>::value, "");
	static_assert( has_front<EV>::value, "");
	static_assert( has_back<EV>::value, "");
	static_assert( has_subscript<EV>::value, "");

	static_assert( has_begin<CEV>::value, "");
	static_assert( has_end<CEV>::value, "");
	static_assert( has_empty<CEV>::value, "");
	static_assert( has_cbegin<CEV>::value, "");
	static_assert( has_cend<CEV>::value, "");
	static_assert( has_operator_bool<CEV>::value, "");
	static_assert( has_data<CEV>::value, "");
	static_assert( has_size<CEV>::value, "");
	static_assert( has_front<CEV>::value, "");
	static_assert( has_back<CEV>::value, "");
	static_assert( has_subscript<CEV>::value, "");

	EV ev{};

	VERIFY(ev.begin() == nullptr);
	VERIFY(ev.end()   == nullptr);
	VERIFY(ev.data()  == nullptr);
	VERIFY(ev.size()  == 0);
	VERIFY(ev.empty());
	VERIFY(ev.cbegin() == nullptr);
	VERIFY(ev.cend()   == nullptr);
	VERIFY((bool)ev    == false);
//	VERIFY(ev.front()  == T{});
//	VERIFY(ev.back()   == T{});
//	VERIFY(ev[0]       == T{});

	VERIFY(hamon::ranges::begin(ev) == nullptr);
	VERIFY(hamon::ranges::end(ev)   == nullptr);
	VERIFY(hamon::ranges::data(ev)  == nullptr);
	VERIFY(hamon::ranges::size(ev)  == 0);
	VERIFY(hamon::ranges::empty(ev));
	VERIFY(hamon::ranges::cbegin(ev) == nullptr);
	VERIFY(hamon::ranges::cend(ev)   == nullptr);

	CEV cev{};

	VERIFY(cev.begin() == nullptr);
	VERIFY(cev.end()   == nullptr);
	VERIFY(cev.data()  == nullptr);
	VERIFY(cev.size()  == 0);
	VERIFY(cev.empty());
	VERIFY(cev.cbegin() == nullptr);
	VERIFY(cev.cend()   == nullptr);
	VERIFY((bool)cev    == false);
//	VERIFY(cev.front()  == T{});
//	VERIFY(cev.back()   == T{});
//	VERIFY(cev[0]       == T{});

	VERIFY(hamon::ranges::begin(cev) == nullptr);
	VERIFY(hamon::ranges::end(cev)   == nullptr);
	VERIFY(hamon::ranges::data(cev)  == nullptr);
	VERIFY(hamon::ranges::size(cev)  == 0);
	VERIFY(hamon::ranges::empty(cev));
	VERIFY(hamon::ranges::cbegin(cev) == nullptr);
	VERIFY(hamon::ranges::cend(cev)   == nullptr);

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	auto e2 = hamon::views::empty<T>;
	static_assert(hamon::is_same<decltype(e2), EV>::value, "");
#endif

	return true;
}

#undef VERIFY

struct A {};

GTEST_TEST(RangesTest, EmptyViewTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test<A>());
}

}	// namespace empty_view_test
}	// namespace hamon_ranges_test
