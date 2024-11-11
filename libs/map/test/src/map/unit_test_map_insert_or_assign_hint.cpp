/**
 *	@file	unit_test_map_insert_or_assign_hint.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class M>
 *	iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);
 *	template<class M>
 *	iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);
 */

#include <hamon/map/map.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_map_try_emplace) && (__cpp_lib_map_try_emplace >= 201411L))

namespace hamon_map_test
{

namespace insert_or_assign_hint_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<Key const&>(), hamon::declval<T>())), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(v.insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<Key&&>(), hamon::declval<T>())), Iterator>::value, "");
		static_assert(!noexcept(v.insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<Key const&>(), hamon::declval<T>())), "");
		static_assert(!noexcept(v.insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<Key&&>(), hamon::declval<T>())), "");
	}

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	{
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert_or_assign(v.begin(), Key{1}, T{30});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert_or_assign(v.begin(), Key{2}, T{40});
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		Key const k{3};
		auto r = v.insert_or_assign(v.end(), k, T{50});
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	{
		Key const k{0};
		auto r = v.insert_or_assign(v.end(), k, T{60});
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{60}});
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, InsertOrAssignHintTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_hint_test

}	// namespace hamon_map_test

#endif
