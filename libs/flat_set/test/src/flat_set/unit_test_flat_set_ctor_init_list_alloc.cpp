/**
 *	@file	unit_test_flat_set_ctor_init_list_alloc.cpp
 *
 *	@brief	initializer_list とアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr flat_set(initializer_list<value_type> il, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_set(initializer_list<value_type> il, const key_compare& comp, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_set(sorted_unique_t, initializer_list<value_type> il, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_set(sorted_unique_t, initializer_list<value_type> il, const key_compare& comp, const Alloc& a);
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

namespace ctor_init_list_alloc_test
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
	using ValueType = typename Set::value_type;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_unique_t, std::initializer_list<ValueType>, Compare const&, Alloc const&>::value, "");

	{
		Alloc const alloc;
		Set v
		{
			{
				Key{1},
				Key{3},
				Key{2},
				Key{3},
			},
			alloc
		};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v
		{
			{
				Key{1},
				Key{3},
				Key{2},
				Key{1},
				Key{2},
			},
			comp,
			alloc
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(it == v.end());
	}
	{
		Alloc const alloc;
		hamon::flat_set<Key, hamon::greater<>, KeyContainer> v
		{
			hamon::sorted_unique,
			{
				Key{4},
				Key{3},
				Key{1},
			},
			alloc
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it == Key{4});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(it == v.end());
	}
	{
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_set<Key, TestLess<Key>, KeyContainer> v
		{
			hamon::sorted_unique,
			{
				Key{1},
				Key{2},
				Key{3},
				Key{4},
			},
			comp,
			alloc
		};
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

GTEST_TEST(FlatSetTest, CtorInitListAllocTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_init_list_alloc_test

}	// namespace hamon_flat_set_test
