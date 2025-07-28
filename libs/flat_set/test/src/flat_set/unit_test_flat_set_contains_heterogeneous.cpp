/**
 *	@file	unit_test_flat_set_contains_heterogeneous.cpp
 *
 *	@brief	contains のテスト
 *
 *	template<class K> constexpr bool contains(const K& x) const;
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace contains_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Set, typename K, typename = void>
struct is_contains_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_contains_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().contains(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set1 = hamon::flat_set<Key, hamon::less<>, KeyContainer>;
	using Set2 = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;
	using Set3 = hamon::flat_set<Key, hamon::greater<>, KeyContainer>;
	using Set4 = hamon::flat_set<Key, hamon::greater<Key>, KeyContainer>;

	static_assert( is_contains_invocable<Set1&, int>::value, "");
	static_assert(!is_contains_invocable<Set2&, int>::value, "");
	static_assert( is_contains_invocable<Set3&, int>::value, "");
	static_assert(!is_contains_invocable<Set4&, int>::value, "");

	static_assert( is_contains_invocable<Set1 const&, int>::value, "");
	static_assert(!is_contains_invocable<Set2 const&, int>::value, "");
	static_assert( is_contains_invocable<Set3 const&, int>::value, "");
	static_assert(!is_contains_invocable<Set4 const&, int>::value, "");

	using Set = Set1;
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<int const&>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<int&&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<int&&>())), "");

	Set const v
	{
		Key{3},
		Key{1},
		Key{4},
		Key{4},
	};
	VERIFY(!v.contains(0));
	VERIFY( v.contains(1));
	VERIFY(!v.contains(2));
	VERIFY( v.contains(3));
	VERIFY( v.contains(4));
	VERIFY(!v.contains(5));

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, ContainsHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>>()));

	{
		hamon::flat_set<hamon::string, hamon::less<>> fs = {"Alice", "Bob", "Carol", "Bob"};

		// lessのvoidに対する特殊化を使用することで、
		// 文字列リテラルをcontains()関数の引数として渡した際に、
		// string型の一時オブジェクトが生成されない。
		EXPECT_TRUE(fs.contains((const char*)"Bob"));
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace contains_heterogeneous_test

}	// namespace hamon_flat_set_test
