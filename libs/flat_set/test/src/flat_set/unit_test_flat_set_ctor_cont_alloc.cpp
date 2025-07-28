/**
 *	@file	unit_test_flat_set_ctor_cont_alloc.cpp
 *
 *	@brief	container_type とアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr flat_set(const container_type& cont, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_set(const container_type& cont, const key_compare& comp, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_set(sorted_unique_t, const container_type& cont, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_set(sorted_unique_t, const container_type& cont, const key_compare& comp, const Alloc& a);
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

namespace ctor_cont_alloc_test
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
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, KeyContainer, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_unique_t, KeyContainer, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, KeyContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_unique_t, KeyContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, KeyContainer, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_unique_t, KeyContainer, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, KeyContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, KeyContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_unique_t, KeyContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_unique_t, KeyContainer, Compare const&, Alloc const&>::value, "");

	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{3}, Key{4}};
		Alloc const alloc;
		Set v{key_cont, alloc};
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
		KeyContainer key_cont {Key{3}, Key{2}, Key{1}, Key{1}, Key{4}, Key{2}};
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v{key_cont, comp, alloc};
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
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		hamon::ranges::sort(key_cont, Compare{});
		Alloc const alloc;
		Set v{hamon::sorted_unique, key_cont, alloc};
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
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}, Key{2}};
		TestLess<Key> const comp{42};
		hamon::ranges::sort(key_cont, comp);
		Alloc const alloc;
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v{hamon::sorted_unique, key_cont, comp, alloc};
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

GTEST_TEST(FlatSetTest, CtorContAllocTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_cont_alloc_test

}	// namespace hamon_flat_set_test
