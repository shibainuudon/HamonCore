/**
 *	@file	unit_test_flat_set_find_heterogeneous.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class K> constexpr iterator find(const K& x);
 *	template<class K> constexpr const_iterator find(const K& x) const;
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

namespace find_heterogeneous_test
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
struct is_find_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_find_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().find(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set1 = hamon::flat_set<Key, hamon::less<>, KeyContainer>;
	using Set2 = hamon::flat_set<Key, hamon::less<Key>, KeyContainer>;
	using Set3 = hamon::flat_set<Key, hamon::greater<>, KeyContainer>;
	using Set4 = hamon::flat_set<Key, hamon::greater<Key>, KeyContainer>;

	static_assert( is_find_invocable<Set1&, int>::value, "");
	static_assert(!is_find_invocable<Set2&, int>::value, "");
	static_assert( is_find_invocable<Set3&, int>::value, "");
	static_assert(!is_find_invocable<Set4&, int>::value, "");

	static_assert( is_find_invocable<Set1 const&, int>::value, "");
	static_assert(!is_find_invocable<Set2 const&, int>::value, "");
	static_assert( is_find_invocable<Set3 const&, int>::value, "");
	static_assert(!is_find_invocable<Set4 const&, int>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<Set1 const&>().find(hamon::declval<int const&>())), typename Set1::const_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().find(hamon::declval<int const&>())), typename Set1::iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set1 const&>().find(hamon::declval<int const&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().find(hamon::declval<int const&>())), "");

	{
		Set1 v
		{
			Key{3},
			Key{6},
			Key{1},
			Key{4},
		};

		VERIFY(v.find(0) == v.end());
		VERIFY(v.find(1) == (v.begin() + 0));
		VERIFY(v.find(2) == v.end());
		VERIFY(v.find(3) == (v.begin() + 1));
		VERIFY(v.find(4) == (v.begin() + 2));
		VERIFY(v.find(5) == v.end());
		VERIFY(v.find(6) == (v.begin() + 3));
		VERIFY(v.find(7) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(0) == cv.end());
		VERIFY(cv.find(1) == (cv.begin() + 0));
		VERIFY(cv.find(2) == cv.end());
		VERIFY(cv.find(3) == (cv.begin() + 1));
		VERIFY(cv.find(4) == (cv.begin() + 2));
		VERIFY(cv.find(5) == cv.end());
		VERIFY(cv.find(6) == (cv.begin() + 3));
		VERIFY(cv.find(7) == cv.end());
	}
	{
		Set3 v
		{
			Key{3},
			Key{6},
			Key{1},
			Key{4},
		};

		VERIFY(v.find(0) == v.end());
		VERIFY(v.find(1) == (v.begin() + 3));
		VERIFY(v.find(2) == v.end());
		VERIFY(v.find(3) == (v.begin() + 2));
		VERIFY(v.find(4) == (v.begin() + 1));
		VERIFY(v.find(5) == v.end());
		VERIFY(v.find(6) == (v.begin() + 0));
		VERIFY(v.find(7) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(0) == cv.end());
		VERIFY(cv.find(1) == (cv.begin() + 3));
		VERIFY(cv.find(2) == cv.end());
		VERIFY(cv.find(3) == (cv.begin() + 2));
		VERIFY(cv.find(4) == (cv.begin() + 1));
		VERIFY(cv.find(5) == cv.end());
		VERIFY(cv.find(6) == (cv.begin() + 0));
		VERIFY(cv.find(7) == cv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, FindHeterogeneousTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>>()));

	{
		hamon::flat_set<hamon::string, hamon::less<>> fs = {"Alice", "Bob", "Carol"};

		// lessのvoidに対する特殊化を使用することで、
		// 文字列リテラルをfind()関数の引数として渡した際に、
		// string型の一時オブジェクトが生成されない。
		decltype(fs)::iterator it = fs.find((const char*)"Bob");
		EXPECT_TRUE(it != fs.end());
		EXPECT_EQ("Bob", *it);
	}
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace find_heterogeneous_test

}	// namespace hamon_flat_set_test
