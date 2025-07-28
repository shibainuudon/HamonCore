/**
 *	@file	unit_test_flat_set_ctor_cont.cpp
 *
 *	@brief	container_type を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit flat_set(container_type cont, const key_compare& comp = key_compare());
 *
 *	constexpr flat_set(sorted_unique_t, container_type cont, const key_compare& comp = key_compare());
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace ctor_cont_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;

	static_assert( hamon::is_constructible<Set, KeyContainer>::value, "");
	static_assert( hamon::is_constructible<Set, KeyContainer, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_unique_t, KeyContainer>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, KeyContainer>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, KeyContainer, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_unique_t, KeyContainer>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, KeyContainer>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, KeyContainer, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_unique_t, KeyContainer>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, KeyContainer>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, KeyContainer, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_unique_t, KeyContainer>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&>::value, "");

	{
		KeyContainer const cont {Key{3}, Key{1}, Key{3}, Key{4}};
		Set v{cont};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
	}
	{
		KeyContainer cont {Key{3}, Key{2}, Key{1}, Key{1}, Key{4}, Key{2}};
		TestLess<Key> const comp{42};
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v{hamon::move(cont), comp};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(*it == Key{4});
		++it;
		VERIFY(it == v.end());
	}
	{
		KeyContainer cont {Key{3}, Key{1}, Key{4}};
		hamon::ranges::sort(cont, Compare{});
		Set v{hamon::sorted_unique, hamon::move(cont)};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
	}
	{
		KeyContainer cont {Key{3}, Key{1}, Key{4}, Key{2}};
		TestLess<Key> const comp{42};
		hamon::ranges::sort(cont, comp);
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v{hamon::sorted_unique, cont, comp};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(*it == Key{4});
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, CtorContTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_cont_test

}	// namespace hamon_flat_set_test
