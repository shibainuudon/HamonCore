/**
 *	@file	unit_test_flat_multimap_emplace_hint.cpp
 *
 *	@brief	emplace_hint のテスト
 *
 *	template<class... Args>
 *	constexpr iterator emplace_hint(const_iterator position, Args&&... args);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace emplace_hint_test
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
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace_hint(hamon::declval<ConstIterator>(), hamon::declval<Key>(), hamon::declval<T>())), "");

	Map v;
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 0);
	{
		auto r = v.emplace_hint(v.cbegin(), Key{1}, T{10});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	{
		auto r = v.emplace_hint(v.cbegin(), Key{1}, T{20});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{20});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	{
		ValueType const t{Key{2}, T{30}};
		auto r = v.emplace_hint(v.cbegin(), t);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	{
		ValueType const t{Key{2}, T{40}};
		auto r = v.emplace_hint(v.cbegin(), t);
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{40});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 4);
	{
		ValueType t{Key{2}, T{50}};
		auto r = v.emplace_hint(v.cbegin(), hamon::move(t));
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{50});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 5);
	{
		ValueType t{Key{0}, T{60}};
		auto r = v.emplace_hint(v.cbegin(), hamon::move(t));
		VERIFY(r->first == Key{0});
		VERIFY(r->second == T{60});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 6);

	return true;
}

template <typename Void, typename T, typename... Args>
struct is_emplace_hint_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_emplace_hint_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().emplace_hint(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_emplace_hint_invocable = is_emplace_hint_invocable_impl<void, T, Args...>;

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}
};

FLAT_MAP_TEST_CONSTEXPR bool test2()
{
#if defined(HAMON_USE_STD_FLAT_MAP)
	namespace ns = std;
#else
	namespace ns = hamon;
#endif

	using Map = hamon::flat_multimap<int, S1>;
	using ConstIterator = typename Map::const_iterator;

	static_assert( is_emplace_hint_invocable<Map&, ConstIterator, int, S1>::value, "");
	static_assert(!is_emplace_hint_invocable<Map&, ConstIterator, int, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Map&, ConstIterator, int, int, int>::value, "");
	static_assert( is_emplace_hint_invocable<Map&, ConstIterator, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");
	static_assert(!is_emplace_hint_invocable<Map const&, ConstIterator, int, S1>::value, "");
	static_assert(!is_emplace_hint_invocable<Map const&, ConstIterator, int, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Map const&, ConstIterator, int, int, int>::value, "");
	static_assert(!is_emplace_hint_invocable<Map const&, ConstIterator, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");

	Map v;

	{
		auto r = v.emplace_hint(v.end(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
//		VERIFY(v.at(1).x == 10);
//		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace_hint(v.cend(),
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(30, 40));
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 30);
		VERIFY(r->second.y == 40);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
//		VERIFY(v.at(1).x == 10);
//		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace_hint(v.cend(),
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
		VERIFY(r->first == 2);
		VERIFY(r->second.x == 50);
		VERIFY(r->second.y == 60);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
//		VERIFY(v.at(1).x == 10);
//		VERIFY(v.at(1).y == 20);
//		VERIFY(v.at(2).x == 50);
//		VERIFY(v.at(2).y == 60);
	}

	return true;
}

FLAT_MAP_TEST_CONSTEXPR bool test3()
{
	using Key = int;
	using T = float;
	using Map = hamon::flat_multimap<Key, T>;
	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
		};

		v.emplace_hint(v.begin(), Key{2}, T{40});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		{
			auto it = v.begin();
			VERIFY(it[0].first == Key{1});
			VERIFY(it[1].first == Key{2});
			VERIFY(it[2].first == Key{2});
			VERIFY(it[3].first == Key{3});
			VERIFY(it[0].second == T{10});
			VERIFY(it[1].second == T{40});
			VERIFY(it[2].second == T{20});
			VERIFY(it[3].second == T{30});
		}

		v.emplace_hint(v.begin() + 3, Key{2}, T{50});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		{
			auto it = v.begin();
			VERIFY(it[0].first == Key{1});
			VERIFY(it[1].first == Key{2});
			VERIFY(it[2].first == Key{2});
			VERIFY(it[3].first == Key{2});
			VERIFY(it[4].first == Key{3});
			VERIFY(it[0].second == T{10});
			VERIFY(it[1].second == T{40});
			VERIFY(it[2].second == T{20});
			VERIFY(it[3].second == T{50});
			VERIFY(it[4].second == T{30});
		}

		v.emplace_hint(v.begin() + 2, Key{2}, T{60});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		{
			auto it = v.begin();
			VERIFY(it[0].first == Key{1});
			VERIFY(it[1].first == Key{2});
			VERIFY(it[2].first == Key{2});
			VERIFY(it[3].first == Key{2});
			VERIFY(it[4].first == Key{2});
			VERIFY(it[5].first == Key{3});
			VERIFY(it[0].second == T{10});
			VERIFY(it[1].second == T{40});
			VERIFY(it[2].second == T{60});
			VERIFY(it[3].second == T{20});
			VERIFY(it[4].second == T{50});
			VERIFY(it[5].second == T{30});
		}

		v.emplace_hint(v.end(), Key{2}, T{70});
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 7);
		{
			auto it = v.begin();
			VERIFY(it[0].first == Key{1});
			VERIFY(it[1].first == Key{2});
			VERIFY(it[2].first == Key{2});
			VERIFY(it[3].first == Key{2});
			VERIFY(it[4].first == Key{2});
			VERIFY(it[5].first == Key{2});
			VERIFY(it[6].first == Key{3});
			VERIFY(it[0].second == T{10});
			VERIFY(it[1].second == T{40});
			VERIFY(it[2].second == T{60});
			VERIFY(it[3].second == T{20});
			VERIFY(it[4].second == T{50});
			VERIFY(it[5].second == T{70});
			VERIFY(it[6].second == T{30});
		}
	}
	return true;
}

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test4()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;

	{
		// was empty
		Map m;
		auto r = m.emplace_hint(m.end(), ValueType(2, 3.5));
		VERIFY(r == m.begin());
		VERIFY(m.size() == 1);
		VERIFY(m.begin()->first == 2);
		VERIFY(m.begin()->second == 3.5);
	}
	{
		// hint correct and no duplicates
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {3, 3.0}});
		auto it = m.begin() + 2;
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 4);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
	}
	{
		// hint correct and at the begin
		Map m = Map(hamon::sorted_equivalent, {{3, 3.0}, {4, 4.0}});
		auto it = m.begin();
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin());
		VERIFY(m.size() == 3);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
	}
	{
		// hint correct and at the end
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}});
		auto it = m.end();
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 3);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
	}
	{
		// hint correct and at first duplicate
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {2, 1.9}, {2, 2.1}, {3, 3.0}});
		auto it = m.begin() + 2;
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 6);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
		VERIFY(hamon::next(r)->first == 2);
		VERIFY(hamon::next(r)->second == 1.9);
	}
	{
		// hint correct and in-between duplicates
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {2, 1.8}, {2, 1.9}, {2, 2.1}, {3, 3.0}});
		auto it = m.begin() + 4;
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 4);
		VERIFY(m.size() == 7);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
		VERIFY(hamon::next(r)->first == 2);
		VERIFY(hamon::next(r)->second == 2.1);
	}
	{
		// hint correct and after duplicates
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {2, 1.8}, {2, 1.9}, {2, 2.1}, {3, 3.0}});
		auto it = m.begin() + 5;
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 5);
		VERIFY(m.size() == 7);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
		VERIFY(hamon::next(r)->first == 3);
		VERIFY(hamon::next(r)->second == 3.0);
	}
	{
		// hint incorrect and no duplicates
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {3, 3.0}});
		auto it = m.begin() + 1;
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 4);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
	}
	{
		// hint incorrect and at the begin
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}});
		auto it = m.begin();
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 3);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
	}
	{
		// hint incorrect and at the end
		Map m = Map(hamon::sorted_equivalent, {{3, 3.0}, {4, 4.0}});
		auto it = m.end();
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		VERIFY(r == m.begin());
		VERIFY(m.size() == 3);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
	}
	{
		// hint incorrect and before the first duplicate
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {2, 1.8}, {2, 1.9}, {2, 2.1}, {3, 3.0}});
		auto it = m.begin();
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		// the result is as left as possible
		VERIFY(r == m.begin() + 2);
		VERIFY(m.size() == 7);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
		VERIFY(hamon::next(r)->first == 2);
		VERIFY(hamon::next(r)->second == 1.8);
	}
	{
		// hint incorrect and after the last duplicate
		Map m = Map(hamon::sorted_equivalent, {{0, 0.0}, {1, 1.0}, {2, 1.8}, {2, 1.9}, {2, 2.1}, {3, 3.0}, {4, 4.0}});
		auto it = m.begin() + 6;
		auto r = m.emplace_hint(it, ValueType(2, 2.0));
		// the result is as right as possible
		VERIFY(r == m.begin() + 5);
		VERIFY(m.size() == 8);
		VERIFY(r->first == 2);
		VERIFY(r->second == 2.0);
		VERIFY(hamon::next(r)->first == 3);
		VERIFY(hamon::next(r)->second == 3.0);
	}

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
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{1}, Key{2}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType(1, 1)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{1}, Key{2}, Key{2}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		KeyContainer   a{Key{1}, Key{3}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType(3, 3)), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		KeyContainer   a{Key{1}, Key{1}, Key{1}, Key{1}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType(1, 5)), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using ValueContainer = TValueContainer<T, ThrowAllocator<T>>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a{Key{4}, Key{4}, Key{4}, Key{4}};
		ValueContainer b({5, 6, 7, 8}, ThrowAllocator<T>{&throw_after});
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ValueType = typename Map::value_type;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.emplace_hint(v.end(), ValueType(0, 0)), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultimapTest, EmplaceHintTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test3());

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::vector<int>, hamon::deque<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::vector<int>, MinSequenceContainer<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::deque<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::deque<int>, hamon::deque<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<hamon::deque<int>, MinSequenceContainer<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<MinSequenceContainer<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<MinSequenceContainer<int>, hamon::deque<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4<MinSequenceContainer<int>, MinSequenceContainer<double>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace emplace_hint_test

}	// namespace hamon_flat_multimap_test
