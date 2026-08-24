/**
 *	@file	unit_test_flat_map_try_emplace_hint.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class... Args>
 *	constexpr iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args);
 *
 *	template<class... Args>
 *	constexpr iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);
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

namespace try_emplace_hint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key const&>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key&&>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key const&>(), hamon::declval<T>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<Key&&>(), hamon::declval<T>())), "");

	Map v;

	{
		auto r = v.try_emplace(v.cbegin(), Key{1}, T{10});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		auto r = v.try_emplace(v.cbegin(), Key{1}, T{20});
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		Key const k{2};
		auto r = v.try_emplace(v.cbegin(), k, T{30});
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		Key const k{2};
		auto r = v.try_emplace(v.cbegin(), k, T{40});
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		auto r = v.try_emplace(v.cbegin(), Key{2}, T{50});
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		auto r = v.try_emplace(v.cbegin(), Key{0}, T{60});
		VERIFY(r->first == Key{0});
		VERIFY(r->second == T{60});
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.at(0) == 60);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);

	return true;
}

template <typename Void, typename T, typename... Args>
struct is_try_emplace_hint_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_try_emplace_hint_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().try_emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_try_emplace_hint_invocable = is_try_emplace_hint_invocable_impl<void, T, Args...>;

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}
};

HAMON_CXX20_CONSTEXPR bool test2()
{
	using Map = hamon::flat_map<int, S1>;
	using ConstIterator = typename Map::const_iterator;

	static_assert( is_try_emplace_hint_invocable<Map&, ConstIterator, int&&, S1 const&>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map&, ConstIterator, int&&, int>::value, "");
	static_assert( is_try_emplace_hint_invocable<Map&, ConstIterator, int&&, int, int>::value, "");
	static_assert( is_try_emplace_hint_invocable<Map&, ConstIterator, int const&, S1>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map&, ConstIterator, int const&, int>::value, "");
	static_assert( is_try_emplace_hint_invocable<Map&, ConstIterator, int const&, int, int>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map&, ConstIterator, hamon::piecewise_construct_t, hamon::tuple<int>, hamon::tuple<int, int>>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, int&&, S1 const&>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, int&&, int>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, int&&, int, int>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, int const&, S1>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, int const&, int>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, int const&, int, int>::value, "");
	static_assert(!is_try_emplace_hint_invocable<Map const&, ConstIterator, hamon::piecewise_construct_t, hamon::tuple<int>, hamon::tuple<int, int>>::value, "");

	Map v;

	{
		auto r = v.try_emplace(v.end(), 1, 10, 20);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.try_emplace(v.cend(), 1, 30, 40);
		VERIFY(r->first == 1);
		VERIFY(r->second.x == 10);
		VERIFY(r->second.y == 20);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.try_emplace(v.cend(), 2, 50, 60);
		VERIFY(r->first == 2);
		VERIFY(r->second.x == 50);
		VERIFY(r->second.y == 60);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(2).x == 50);
		VERIFY(v.at(2).y == 60);
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
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		int throw_after = INT_MAX;

		KeyContainer   a({Key{1}, Key{2}, Key{3}, Key{4}}, ThrowAllocator<Key>{&throw_after});
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		throw_after = 1;

		EXPECT_THROW(v.try_emplace(v.end(), 0, 0), std::bad_alloc);
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
		EXPECT_THROW(v.try_emplace(v.end(), k, 0), std::bad_alloc);
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
		EXPECT_THROW(v.try_emplace(v.end(), k, 0), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.try_emplace(v.end(), 0, 0), int);
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

		EXPECT_THROW(v.try_emplace(v.end(), 0, 0), std::bad_alloc);
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
		EXPECT_THROW(v.try_emplace(v.end(), k, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, TryEmplaceHintTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();
}

}	// namespace try_emplace_hint_test

}	// namespace hamon_flat_map_test
