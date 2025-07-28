/**
 *	@file	unit_test_flat_multiset_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K> constexpr size_type count(const K& x) const;
 */

#include <hamon/flat_set/flat_multiset.hpp>
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
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace count_heterogeneous_test
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
struct is_count_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_count_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().count(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set1 = hamon::flat_multiset<Key, hamon::less<>, KeyContainer>;
	using Set2 = hamon::flat_multiset<Key, hamon::less<Key>, KeyContainer>;
	using Set3 = hamon::flat_multiset<Key, hamon::greater<>, KeyContainer>;
	using Set4 = hamon::flat_multiset<Key, hamon::greater<Key>, KeyContainer>;

	static_assert( is_count_invocable<Set1&, int>::value, "");
	static_assert(!is_count_invocable<Set2&, int>::value, "");
	static_assert( is_count_invocable<Set3&, int>::value, "");
	static_assert(!is_count_invocable<Set4&, int>::value, "");

	static_assert( is_count_invocable<Set1 const&, int>::value, "");
	static_assert(!is_count_invocable<Set2 const&, int>::value, "");
	static_assert( is_count_invocable<Set3 const&, int>::value, "");
	static_assert(!is_count_invocable<Set4 const&, int>::value, "");

	using Set = Set1;
	using SizeType = typename Set::size_type;
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int&&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int&&>())), "");

	Set const v
	{
		Key{3},
		Key{1},
		Key{4},
		Key{3},
	};
	VERIFY(v.count(0) == 0);
	VERIFY(v.count(1) == 1);
	VERIFY(v.count(2) == 0);
	VERIFY(v.count(3) == 2);
	VERIFY(v.count(4) == 1);
	VERIFY(v.count(5) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, CountHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>>()));

	{
		hamon::flat_multiset<hamon::string, hamon::less<>> fs = {"Alice", "Bob", "Carol", "Bob"};

		// lessのvoidに対する特殊化を使用することで、
		// 文字列リテラルをcount()関数の引数として渡した際に、
		// string型の一時オブジェクトが生成されない。
		EXPECT_EQ(2u, fs.count((const char*)"Bob"));
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_flat_multiset_test
