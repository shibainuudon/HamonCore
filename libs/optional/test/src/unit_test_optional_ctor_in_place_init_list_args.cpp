/**
 *	@file	unit_test_optional_ctor_in_place_init_list_args.cpp
 *
 *	@brief	in_place_tとinitializer_listとArgs...を引数に取るコンストラクタのテスト
 *
 *	template<class U, class... Args>
 *	constexpr explicit optional(in_place_t, initializer_list<U> il, Args&&... args);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_optional_test
{

namespace ctor_in_place_init_list_args_test
{

struct X
{
	hamon::size_t m_size;
	HAMON_CXX14_CONSTEXPR X(std::initializer_list<int> il)
		: m_size(il.size()) {}
};

struct Y
{
	hamon::size_t m_size;
	int           m_value;
	HAMON_CXX14_CONSTEXPR Y(std::initializer_list<int> il, int v)
		: m_size(il.size()), m_value(v) {}
};

struct Noexcept1
{
	Noexcept1(std::initializer_list<int>) noexcept(true);
	Noexcept1(std::initializer_list<int>, int) noexcept(false);
};

struct Noexcept2
{
	Noexcept2(std::initializer_list<int>) noexcept(false);
	Noexcept2(std::initializer_list<int>, int) noexcept(true);
};

static_assert(!hamon::is_constructible<hamon::optional<int>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<int>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_constructible<hamon::optional<X>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<X>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_constructible<hamon::optional<Y>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert( hamon::is_constructible<hamon::optional<Y>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");

#if !defined(HAMON_USE_STD_OPTIONAL)
static_assert(!hamon::is_nothrow_constructible<hamon::optional<X>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<Y>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::optional<Noexcept1>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<Noexcept1>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::optional<Noexcept2>, hamon::in_place_t, std::initializer_list<int>>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::optional<Noexcept2>, hamon::in_place_t, std::initializer_list<int>, int>::value, "");
#endif

GTEST_TEST(OptionalTest, CtorInPlaceInitListArgsTest)
{
	{
		std::allocator<int> alloc;
		hamon::optional<std::vector<int>> t { hamon::in_place, {3, 1, 4}, alloc };
		EXPECT_EQ(3, t.value()[0]);
		EXPECT_EQ(1, t.value()[1]);
		EXPECT_EQ(4, t.value()[2]);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::optional<X> t{hamon::in_place, {1,2,3}};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(t.value().m_size, 3u);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(t->m_size, 3u);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::optional<Y> t{hamon::in_place, {1,2}, 42};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(t.value().m_size, 2u);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(t.value().m_value, 42);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(t->m_size, 2u);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(t->m_value, 42);
	}
}

}	// namespace ctor_in_place_init_list_args_test

}	// namespace hamon_optional_test
