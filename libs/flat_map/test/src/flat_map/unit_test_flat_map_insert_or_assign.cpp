/**
 *	@file	unit_test_flat_map_insert_or_assign.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class M>
 *	constexpr pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
 *
 *	template<class M>
 *	constexpr pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
 */

#include <hamon/flat_map/flat_map.hpp>
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
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace insert_or_assign_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_FLAT_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T const&>())), "");

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{3}] == T{20});

	{
		auto r = v.insert_or_assign(Key{1}, T{30});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{3}] == T{20});
	{
		auto r = v.insert_or_assign(Key{2}, T{40});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{40});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{20});
	{
		Key const k{3};
		auto r = v.insert_or_assign(k, T{50});
		VERIFY(r.first->first == Key{3});
		VERIFY(r.first->second == T{50});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{50});
	{
		Key const k{0};
		auto r = v.insert_or_assign(k, T{60});
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 4);
	VERIFY(v[Key{0}] == T{60});
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{50});

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.insert_or_assign(0, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		Key const k{0};
		EXPECT_THROW(v.insert_or_assign(k, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		Key const k{0};
		EXPECT_THROW(v.insert_or_assign(k, 0), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.insert_or_assign(0, 0), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.insert_or_assign(0, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		Key const k{0};
		EXPECT_THROW(v.insert_or_assign(k, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, InsertOrAssignTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		hamon::flat_map<hamon::string, int> fm;

		auto r1 = fm.insert_or_assign("foo", 42);
		EXPECT_TRUE(r1.first->first == "foo");
		EXPECT_TRUE(r1.first->second == 42);
		EXPECT_TRUE(r1.second == true);

		auto r2 = fm.insert_or_assign("foo", 0);
		EXPECT_TRUE(r2.first->first == "foo");
		EXPECT_TRUE(r2.first->second == 0);
		EXPECT_TRUE(r2.second == false);
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_test

}	// namespace hamon_flat_map_test
