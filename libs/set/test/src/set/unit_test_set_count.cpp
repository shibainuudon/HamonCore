/**
 *	@file	unit_test_set_count.cpp
 *
 *	@brief	count のテスト
 *
 *	size_type      count(const key_type& x) const;
 *	template<class K> size_type count(const K& x) const;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace count_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// size_type count(const key_type& x) const;
template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");

	Set const v {Key{1}, Key{4}, Key{1}, Key{1}, Key{3}, Key{3}};

	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 1);
	VERIFY(v.count(Key{5}) == 0);

	return true;
}

#if !defined(HAMON_USE_STD_SET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

struct S
{
	int value;

	constexpr explicit S(int v) : value(v) {}

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

// template<class K> size_type count(const K& x) const;
SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::set<S, hamon::less<>>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int const&>())), "");

	Set const v {S{0}, S{1}, S{4}, S{5}, S{1}, S{5}, S{5}};

	VERIFY(v.count(0) == 1);
	VERIFY(v.count(1) == 1);
	VERIFY(v.count(2) == 0);
	VERIFY(v.count(3) == 0);
	VERIFY(v.count(4) == 1);
	VERIFY(v.count(5) == 1);
	VERIFY(v.count(6) == 0);

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(SetTest, CountTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

#if !defined(HAMON_USE_STD_SET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
#endif
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace count_test

}	// namespace hamon_set_test
