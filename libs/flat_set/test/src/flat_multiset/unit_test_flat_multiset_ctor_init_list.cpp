/**
 *	@file	unit_test_flat_multiset_ctor_init_list.cpp
 *
 *	@brief	initializer_list を引数に取るコンストラクタのテスト
 *
 *	constexpr flat_multiset(initializer_list<value_type> il, const key_compare& comp = key_compare());
 *
 *	constexpr flat_multiset(sorted_equivalent_t, initializer_list<value_type> il, const key_compare& comp = key_compare());
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace ctor_init_list_test
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
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using ValueType = typename Set::value_type;

	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	{
		Set v
		{
			Key{1},
			Key{3},
			Key{2},
			Key{1},
		};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		TestLess<Key> const comp{42};
		hamon::flat_multiset<Key, TestLess<Key>, KeyContainer> v
		{
			{
				Key{1},
				Key{3},
				Key{2},
				Key{2},
				Key{1},
				Key{1},
			},
			comp
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
		++it;
		VERIFY(it == v.end());
	}
	{
		hamon::flat_multiset<Key, hamon::greater<>, KeyContainer> v
		{
			hamon::sorted_equivalent,
			{
				Key{4},
				Key{4},
				Key{3},
				Key{1},
			}
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it == Key{4});
		++it;
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
		hamon::flat_multiset<Key, TestLess<Key>, KeyContainer> v
		{
			hamon::sorted_equivalent,
			{
				Key{1},
				Key{1},
				Key{2},
				Key{2},
				Key{2},
				Key{3},
				Key{3},
				Key{4},
			},
			comp
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 8);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{1});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{2});
		++it;
		VERIFY(*it == Key{3});
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

GTEST_TEST(FlatMultisetTest, CtorInitListTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_init_list_test

}	// namespace hamon_flat_multiset_test
