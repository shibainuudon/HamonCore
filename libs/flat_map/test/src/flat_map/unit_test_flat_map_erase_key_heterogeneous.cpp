/**
 *	@file	unit_test_flat_map_erase_key_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> constexpr size_type erase(K&& x);
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

namespace erase_key_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_erase_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_erase_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().erase(hamon::declval<K>()))>>
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

	static_assert( is_erase_invocable<Map1&, int>::value, "");
	static_assert(!is_erase_invocable<Map2&, int>::value, "");
	static_assert( is_erase_invocable<Map3&, int>::value, "");
	static_assert(!is_erase_invocable<Map4&, int>::value, "");

	static_assert(!is_erase_invocable<Map1 const&, int>::value, "");
	static_assert(!is_erase_invocable<Map2 const&, int>::value, "");
	static_assert(!is_erase_invocable<Map3 const&, int>::value, "");
	static_assert(!is_erase_invocable<Map4 const&, int>::value, "");

	{
		using Map = Map1;
		using SizeType = typename Map::size_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<int const&>())), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<int&&>())), SizeType>::value, "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int&&>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v[1] == T{20});
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(0) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v[1] == T{20});
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(1) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(2) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(3) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(4) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());

		VERIFY(v.erase(5) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		using Map = Map3;
		using SizeType = typename Map::size_type;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<int const&>())), SizeType>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<int&&>())), SizeType>::value, "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int&&>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v[1] == T{20});
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(0) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v[1] == T{20});
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(1) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(2) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(v[3] == T{10});
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(3) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 1);
		VERIFY(v[4] == T{30});

		VERIFY(v.erase(4) == 1);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());

		VERIFY(v.erase(5) == 0);

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}

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
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.erase(1), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_map<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_unique, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.erase(2), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, EraseKeyHeterogeneousTest)
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

}	// namespace erase_key_heterogeneous_test

}	// namespace hamon_flat_map_test
