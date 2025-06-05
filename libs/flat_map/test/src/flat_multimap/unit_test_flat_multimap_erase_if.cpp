/**
 *	@file	unit_test_flat_multimap_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class Key, class T, class Compare, class KeyContainer, class MappedContainer, class Predicate>
 *	constexpr typename flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>::size_type
 *	erase_if(flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>& c, Predicate pred);
 */

#include <hamon/flat_map/flat_multimap.hpp>
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
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace erase_if_test
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
	using ConstReference = typename Map::const_reference;
	using ValueType = typename Map::value_type;
	using SizeType = typename Map::size_type;

	struct F1
	{
		constexpr bool operator()(ConstReference x) const noexcept
		{
			return x.first < 3;
		}
	};

	struct F2
	{
		constexpr bool operator()(ValueType x) const
		{
			return x.first == 3;
		}
	};

	static_assert(hamon::is_same<decltype(hamon::erase_if(hamon::declval<Map&>(), F1{})), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::erase_if(hamon::declval<Map&>(), F2{})), SizeType>::value, "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Map&>(), F1{})), "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Map&>(), F2{})), "");

	{
		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{5}, T{40}},
			{Key{2}, T{50}},
			{Key{1}, T{60}},
		};

		auto r = hamon::erase_if(v, F1{});
		VERIFY(r == 3);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{5}, T{40}},
			{Key{2}, T{50}},
			{Key{1}, T{60}},
		};

		auto r = hamon::erase_if(v, F2{});
		VERIFY(r == 1);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		Map v;
		auto r = hamon::erase_if(v, F1{});
		VERIFY(r == 0);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
	}
	{
		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		auto r = hamon::erase_if(v, [](ValueType){return true;});
		VERIFY(r == 3);
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
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
		using KeyContainer = ThrowOnEraseContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ConstReference = typename Map::const_reference;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		EXPECT_THROW(hamon::erase_if(v, [](ConstReference x){return x.first % 2 == 0;}), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;
		using ConstReference = typename Map::const_reference;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		EXPECT_THROW(hamon::erase_if(v, [](ConstReference x){return x.first > 3;}), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultimapTest, EraseIfTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		using value_type = typename hamon::flat_multimap<hamon::string, int>::value_type;

		hamon::flat_multimap<hamon::string, int> fm =
		{
			{"A", 3},
			{"B", 1},
			{"B", 4},
			{"C", 5},
		};

		// コンテナfmから、キーが"B"の要素をすべて削除する
		auto num = hamon::erase_if(fm, [](const value_type& x) { return x.first == "B"; });
		EXPECT_TRUE(num == 2);

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":" << p.second << ", ";
		}
		EXPECT_EQ("A:3, C:5, ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace erase_if_test

}	// namespace hamon_flat_multimap_test
