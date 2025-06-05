/**
 *	@file	unit_test_flat_map_try_emplace.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class... Args>
 *	constexpr pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);
 *
 *	template<class... Args>
 *	constexpr pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/memory.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace try_emplace_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<Key const&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<Key&&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<Key const&>(), hamon::declval<T>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<Key&&>(), hamon::declval<T>())), "");

	Map v;
	VERIFY(check_invariant(v));

	{
		auto r = v.try_emplace(Key{1}, T{10});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		auto r = v.try_emplace(Key{1}, T{20});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		Key const k{2};
		auto r = v.try_emplace(k, T{30});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		Key const k{2};
		auto r = v.try_emplace(k, T{40});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		auto r = v.try_emplace(Key{2}, T{50});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		auto r = v.try_emplace(Key{0}, T{60});
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);
	}
	VERIFY(check_invariant(v));
	VERIFY(v.size() == 3);
	VERIFY(v.at(0) == 60);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);

	return true;
}

template <typename Void, typename T, typename... Args>
struct is_try_emplace_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_try_emplace_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().try_emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_try_emplace_invocable = is_try_emplace_invocable_impl<void, T, Args...>;

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

	using Map = hamon::flat_map<int, S1>;

	static_assert( is_try_emplace_invocable<Map&, int&&, S1 const&>::value, "");
	static_assert(!is_try_emplace_invocable<Map&, int&&, int>::value, "");
	static_assert( is_try_emplace_invocable<Map&, int&&, int, int>::value, "");
	static_assert( is_try_emplace_invocable<Map&, int const&, S1>::value, "");
	static_assert(!is_try_emplace_invocable<Map&, int const&, int>::value, "");
	static_assert( is_try_emplace_invocable<Map&, int const&, int, int>::value, "");
	static_assert(!is_try_emplace_invocable<Map&, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, int&&, S1>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, int&&, int>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, int&&, int, int>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, int const&, S1 const&>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, int const&, int>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, int const&, int, int>::value, "");
	static_assert(!is_try_emplace_invocable<Map const&, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");

	Map v;

	{
		auto r = v.try_emplace(1, 10, 20);
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == true);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.try_emplace(1, 30, 40);
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == false);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		int const k = 2;
		auto r = v.try_emplace(k, 50, 60);
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second.x == 50);
		VERIFY(r.first->second.y == 60);
		VERIFY(r.second == true);

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

		EXPECT_THROW(v.try_emplace(0, 0), std::bad_alloc);
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
		EXPECT_THROW(v.try_emplace(k, 0), std::bad_alloc);
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
		EXPECT_THROW(v.try_emplace(k, 0), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = EmplaceUnsafeContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.try_emplace(0, 0), int);
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

		EXPECT_THROW(v.try_emplace(0, 0), std::bad_alloc);
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
		EXPECT_THROW(v.try_emplace(k, 0), std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, TryEmplaceTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		hamon::flat_map<int, hamon::unique_ptr<int>> fm;

		auto u1 = hamon::make_unique<int>(114);
		auto r1 = fm.try_emplace(42, hamon::move(u1));
		EXPECT_TRUE(u1.get() == nullptr);
		EXPECT_TRUE(r1.first->first == 42);
		EXPECT_TRUE(*r1.first->second == 114);
		EXPECT_TRUE(r1.second == true);

		auto u2 = hamon::make_unique<int>(514);
		auto r2 = fm.try_emplace(42, hamon::move(u2));
		EXPECT_TRUE(u2.get() != nullptr);
		EXPECT_TRUE(r2.first->first == 42);
		EXPECT_TRUE(*r2.first->second == 114);
		EXPECT_TRUE(r2.second == false);
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace try_emplace_test

}	// namespace hamon_flat_map_test
