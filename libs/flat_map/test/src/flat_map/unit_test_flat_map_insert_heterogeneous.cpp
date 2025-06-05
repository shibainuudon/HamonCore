/**
 *	@file	unit_test_flat_map_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class P> constexpr pair<iterator, bool> insert(P&& x);
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
#include <gtest/gtest.h>
#include <array>
#include <string>
#include <tuple>
#include <utility>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace insert_heterogeneous_test
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

	// from std::pair
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, int>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<double, long>>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, int>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<double, long>>())), "");
	{
		Map v;
		VERIFY(check_invariant(v));
		{
			auto r = v.insert(std::make_pair(1, 10.0f));
			VERIFY(r.first->first == Key{1});
			VERIFY(r.first->second == T{10});
			VERIFY(r.second == true);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v[Key{1}] == T{10});
		{
			auto const p = std::make_pair(char{2}, 20.0);
			auto r = v.insert(p);
			VERIFY(r.first->first == Key{2});
			VERIFY(r.first->second == T{20});
			VERIFY(r.second == true);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
		{
			auto r = v.insert(std::make_pair(short{1}, 30.0f));
			VERIFY(r.first->first == Key{1});
			VERIFY(r.first->second == T{10});
			VERIFY(r.second == false);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
	}

	// from std::tuple
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<int, int>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, float>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::tuple<double, long>>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<int, int>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<char, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::tuple<double, long>>())), "");
	{
		Map v;
		VERIFY(check_invariant(v));
		{
			auto r = v.insert(std::make_tuple(1, 10.0f));
			VERIFY(r.first->first == Key{1});
			VERIFY(r.first->second == T{10});
			VERIFY(r.second == true);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v[Key{1}] == T{10});
		{
			auto const p = std::make_tuple(char{2}, 20.0);
			auto r = v.insert(p);
			VERIFY(r.first->first == Key{2});
			VERIFY(r.first->second == T{20});
			VERIFY(r.second == true);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
		{
			auto r = v.insert(std::make_tuple(short{1}, 30.0f));
			VERIFY(r.first->first == Key{1});
			VERIFY(r.first->second == T{10});
			VERIFY(r.second == false);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
	}

	// from std::array
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<int, 2>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<char, 2>>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::array<double, 2>>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<int, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<char, 2>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::array<double, 2>>())), "");
	{
		Map v;
		VERIFY(check_invariant(v));
		{
			auto r = v.insert(std::array<int, 2>{1, 10});
			VERIFY(r.first->first == Key{1});
			VERIFY(r.first->second == T{10});
			VERIFY(r.second == true);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v[Key{1}] == T{10});
		{
			auto const p = std::array<char, 2>{2, 20};
			auto r = v.insert(p);
			VERIFY(r.first->first == Key{2});
			VERIFY(r.first->second == T{20});
			VERIFY(r.second == true);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
		{
			auto r = v.insert(std::array<short, 2>{1, 30});
			VERIFY(r.first->first == Key{1});
			VERIFY(r.first->second == T{10});
			VERIFY(r.second == false);
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{20});
	}

	return true;
}

template <typename Map, typename P, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Map, typename P>
struct is_insert_invocable<Map, P, hamon::void_t<decltype(hamon::declval<Map>().insert(hamon::declval<P>()))>>
	: public hamon::true_type {};

FLAT_MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::flat_map<int, int>;

	static_assert( is_insert_invocable<Map&, std::pair<int, int>>::value, "");
	static_assert( is_insert_invocable<Map&, std::pair<char, float>>::value, "");
	static_assert(!is_insert_invocable<Map&, std::pair<int, std::string>>::value, "");
	static_assert( is_insert_invocable<Map&, std::tuple<int, int>>::value, "");
	static_assert( is_insert_invocable<Map&, std::tuple<char, float>>::value, "");
	static_assert(!is_insert_invocable<Map&, std::tuple<int, int, int>>::value, "");
	static_assert( is_insert_invocable<Map&, std::array<int, 2>>::value, "");
	static_assert(!is_insert_invocable<Map&, std::array<int, 3>>::value, "");

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

		EXPECT_THROW(v.insert(std::make_pair(0, 0)), std::bad_alloc);
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

		EXPECT_THROW(v.insert(std::make_tuple(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.insert(std::array<int, 2>{0, 0}), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.insert(std::make_pair(0, 0)), int);
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

		EXPECT_THROW(v.insert(std::make_tuple(0, 0)), std::bad_alloc);
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

		EXPECT_THROW(v.insert(std::array<int, 2>{0, 0}), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, InsertHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<char>, hamon::vector<double>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<short>, hamon::deque<float>, hamon::less<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<int>, hamon::vector<double>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<long>, hamon::deque<float>, hamon::greater<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<double>, hamon::less<int>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_flat_map_test
