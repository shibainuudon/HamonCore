/**
 *	@file	unit_test_flat_map_try_emplace_heterogeneous.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class K, class... Args>
 *	constexpr pair<iterator, bool> try_emplace(K&& k, Args&&... args);
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

namespace try_emplace_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename T, typename... Args>
struct is_try_emplace_invocable_impl
	: hamon::false_type {};

template <typename T, typename... Args>
struct is_try_emplace_invocable_impl<
	hamon::void_t<decltype(hamon::declval<T>().try_emplace(hamon::declval<Args>()...))>, T, Args...>
	: hamon::true_type {};

template <typename T, typename... Args>
using is_try_emplace_invocable = is_try_emplace_invocable_impl<void, T, Args...>;

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map1 = hamon::flat_map<Key, T, hamon::less<>, KeyContainer, MappedContainer>;
	using Map2 = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using Map3 = hamon::flat_map<Key, T, hamon::greater<>, KeyContainer, MappedContainer>;
	using Map4 = hamon::flat_map<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

	static_assert( is_try_emplace_invocable<Map1&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map2&, int, T>::value, "");
	static_assert( is_try_emplace_invocable<Map3&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map4&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map1 const&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map2 const&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map3 const&, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map4 const&, int, T>::value, "");

	using Map = Map1;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_FLAT_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<int const&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<int&&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<int const&>(), hamon::declval<T>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<int&&>(), hamon::declval<T>())), "");

	Map v;

	{
		auto r = v.try_emplace(1, T{10});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		auto r = v.try_emplace(1, T{20});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 1);
	VERIFY(v.at(1) == 10);
	{
		int const k{2};
		auto r = v.try_emplace(k, T{30});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		int const k{2};
		auto r = v.try_emplace(k, T{40});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		auto r = v.try_emplace(2, T{50});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v.at(1) == 10);
	VERIFY(v.at(2) == 30);
	{
		auto r = v.try_emplace(0, T{60});
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

#undef VERIFY

GTEST_TEST(FlatMapTest, TryEmplaceHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<char>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace try_emplace_heterogeneous_test

}	// namespace hamon_flat_map_test
