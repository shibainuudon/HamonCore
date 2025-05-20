/**
 *	@file	unit_test_expected_emplace_init_list.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class U, class... Args>
 *	constexpr T& emplace(initializer_list<U> il, Args&&... args) noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace emplace_init_list_test
{

template <typename Void, typename T, typename... Args>
struct CanEmplaceImpl
	: hamon::false_type {};

template <typename T, typename... Args>
struct CanEmplaceImpl<
	hamon::void_t<decltype(hamon::declval<T&>().emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using CanEmplace = CanEmplaceImpl<void, T, Args...>;

template <bool Noexcept1, bool Noexcept2>
struct CtorFromInitializerList
{
	CtorFromInitializerList(std::initializer_list<int>&) noexcept(Noexcept1);
	CtorFromInitializerList(std::initializer_list<int>&, int) noexcept(Noexcept2);
};

static_assert( CanEmplace<hamon::expected<CtorFromInitializerList<true, true>, int>, std::initializer_list<int>&>::value, "");
static_assert( CanEmplace<hamon::expected<CtorFromInitializerList<true, true>, int>, std::initializer_list<int>&, int>::value, "");
static_assert( CanEmplace<hamon::expected<CtorFromInitializerList<true, false>, int>, std::initializer_list<int>&>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInitializerList<true, false>, int>, std::initializer_list<int>&, int>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInitializerList<false, true>, int>, std::initializer_list<int>&>::value, "");
static_assert( CanEmplace<hamon::expected<CtorFromInitializerList<false, true>, int>, std::initializer_list<int>&, int>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInitializerList<false, false>, int>, std::initializer_list<int>&>::value, "");
static_assert(!CanEmplace<hamon::expected<CtorFromInitializerList<false, false>, int>, std::initializer_list<int>&, int>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Data
{
	std::initializer_list<int> il;
	int i;

	constexpr Data(std::initializer_list<int>& l, int ii) noexcept : il(l), i(ii) {}
};

HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(noexcept(hamon::declval<hamon::expected<Data, int>&>().emplace(
		hamon::declval<std::initializer_list<int>>(), hamon::declval<int>())), "");

	{
		auto list1 = {1, 2, 3};
		auto list2 = {4, 5, 6};
		hamon::expected<Data, int> e(hamon::in_place, list1, 5);
		auto& x = e.emplace(list2, 10);
		static_assert(hamon::is_same<decltype(x), Data&>::value, "");
		VERIFY(&x == &(*e));

		VERIFY(e.has_value());
		VERIFY(hamon::ranges::equal(e.value().il, list2));
		VERIFY(e.value().i == 10);
	}
	{
		auto list = {4, 5, 6};
		hamon::expected<Data, int> e(hamon::unexpect, 5);
		auto& x = e.emplace(list, 10);
		static_assert(hamon::is_same<decltype(x), Data&>::value, "");
		VERIFY(&x == &(*e));

		VERIFY(e.has_value());
		VERIFY(hamon::ranges::equal(e.value().il, list));
		VERIFY(e.value().i == 10);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, EmplaceInitListTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace emplace_init_list_test

}	// namespace hamon_expected_test
