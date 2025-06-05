/**
 *	@file	unit_test_flat_map_insert_or_assign_heterogeneous_hint.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class K, class M>
 *	constexpr iterator insert_or_assign(const_iterator hint, K&& k, M&& obj);
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
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace insert_or_assign_heterogeneous_hint_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename I, typename K, typename M, typename = void>
struct is_insert_or_assign_invocable
	: public hamon::false_type {};

template <typename Map, typename I, typename K, typename M>
struct is_insert_or_assign_invocable<Map, I, K, M, hamon::void_t<decltype(hamon::declval<Map>().insert_or_assign(hamon::declval<I>(), hamon::declval<K>(), hamon::declval<M>()))>>
	: public hamon::true_type {};

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map1 = hamon::flat_map<Key, T, hamon::less<>, KeyContainer, MappedContainer>;
	using Map2 = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using Map3 = hamon::flat_map<Key, T, hamon::greater<>, KeyContainer, MappedContainer>;
	using Map4 = hamon::flat_map<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

	static_assert( is_insert_or_assign_invocable<Map1&, typename Map1::const_iterator, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map2&, typename Map2::const_iterator, int, T>::value, "");
	static_assert( is_insert_or_assign_invocable<Map3&, typename Map3::const_iterator, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map4&, typename Map4::const_iterator, int, T>::value, "");

	static_assert(!is_insert_or_assign_invocable<Map1 const&, typename Map1::const_iterator, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map2 const&, typename Map2::const_iterator, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map3 const&, typename Map3::const_iterator, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map4 const&, typename Map4::const_iterator, int, T>::value, "");

	using Map = Map1;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<int const&>(), hamon::declval<T const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<int&&>(), hamon::declval<T const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<int const&>(), hamon::declval<T const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<ConstIterator>(), hamon::declval<int&&>(), hamon::declval<T const&>())), "");

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
		auto r = v.insert_or_assign(v.begin(), 1, T{30});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{30});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{3}] == T{20});
	{
		auto r = v.insert_or_assign(v.end(), 2, T{40});
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{40});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{20});
	{
		int const k{3};
		auto r = v.insert_or_assign(v.cbegin(), k, T{50});
		VERIFY(r->first == Key{3});
		VERIFY(r->second == T{50});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{50});
	{
		int const k{0};
		auto r = v.insert_or_assign(v.cend(), k, T{60});
		VERIFY(r->first == Key{0});
		VERIFY(r->second == T{60});
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
	using Key = TransparentKey;
	using T = int;
	using Comp = hamon::less<>;
	{
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.insert_or_assign(v.begin(), 0, 0), std::bad_alloc);
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

		int const k{0};
		EXPECT_THROW(v.insert_or_assign(v.begin(), k, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = EmplaceUnsafeContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		int const k{0};
		EXPECT_THROW(v.insert_or_assign(v.begin(), k, 0), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.insert_or_assign(v.begin(), 0, 0), int);
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

		EXPECT_THROW(v.insert_or_assign(v.begin(), 0, 0), std::bad_alloc);
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

		int const k{0};
		EXPECT_THROW(v.insert_or_assign(v.begin(), k, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, InsertOrAssignHeterogeneousHintTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<long>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_heterogeneous_hint_test

}	// namespace hamon_flat_map_test
