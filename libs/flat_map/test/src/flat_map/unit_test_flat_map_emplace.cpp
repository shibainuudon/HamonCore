/**
 *	@file	unit_test_flat_map_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args>
 *	constexpr pair<iterator, bool> emplace(Args&&... args);
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
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace emplace_test
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
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_FLAT_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace()), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<ValueType const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().emplace(hamon::declval<Key>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace()), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().emplace(hamon::declval<Key>(), hamon::declval<T>())), "");

	Map v;
	VERIFY(v.size() == 0);
	{
		auto r = v.emplace(Key{1}, T{10});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		auto r = v.emplace(Key{1}, T{20});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		ValueType const t{Key{2}, T{30}};
		auto r = v.emplace(t);
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		ValueType const t{Key{2}, T{40}};
		auto r = v.emplace(t);
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		ValueType t{Key{2}, T{50}};
		auto r = v.emplace(hamon::move(t));
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		ValueType t{Key{0}, T{60}};
		auto r = v.emplace(hamon::move(t));
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 3);
	VERIFY(v.at(0) == 60);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);

	return true;
}

template <typename Void, typename T, typename... Args>
struct is_emplace_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_emplace_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_emplace_invocable = is_emplace_invocable_impl<void, T, Args...>;

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

	static_assert( is_emplace_invocable<Map&, int, S1>::value, "");
	static_assert(!is_emplace_invocable<Map&, int, int>::value, "");
	static_assert(!is_emplace_invocable<Map&, int, int, int>::value, "");
	static_assert( is_emplace_invocable<Map&, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");
	static_assert(!is_emplace_invocable<Map const&, int, S1>::value, "");
	static_assert(!is_emplace_invocable<Map const&, int, int>::value, "");
	static_assert(!is_emplace_invocable<Map const&, int, int, int>::value, "");
	static_assert(!is_emplace_invocable<Map const&, ns::piecewise_construct_t, ns::tuple<int>, ns::tuple<int, int>>::value, "");

	Map v;

	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(10, 20));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(1),
			ns::forward_as_tuple(30, 40));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second.x == 10);
		VERIFY(r.first->second.y == 20);
		VERIFY(r.second == false);

		VERIFY(v.size() == 1);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
	}
	{
		auto r = v.emplace(
			ns::piecewise_construct,
			ns::forward_as_tuple(2),
			ns::forward_as_tuple(50, 60));
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second.x == 50);
		VERIFY(r.first->second.y == 60);
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		VERIFY(v.at(1).x == 10);
		VERIFY(v.at(1).y == 20);
		VERIFY(v.at(2).x == 50);
		VERIFY(v.at(2).y == 60);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, EmplaceTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace emplace_test

}	// namespace hamon_flat_map_test
