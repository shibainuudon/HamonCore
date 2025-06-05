/**
 *	@file	unit_test_flat_multimap_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator erase(iterator position);
 *	constexpr iterator erase(const_iterator position);
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
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace erase_position_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;

	{
		using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
			{Key{2}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.begin());
			VERIFY(it == v.begin());
			VERIFY(it->first == Key{2});
			//VERIFY(it->second == T{10});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.begin() + 1);
			VERIFY(it == v.begin() + 1);
			VERIFY(it->first == Key{3});
			//VERIFY(it->second == T{10});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.begin() + 1);
			VERIFY(it == v.begin() + 1);
			VERIFY(it->first == Key{3});
			//VERIFY(it->second == T{10});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 2);
		{
			auto it = v.erase(v.begin() + 2);
			VERIFY(it == v.end());
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 2);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
	}
	{
		using Map = hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
			{Key{2}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 6);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		{
			auto it = v.erase(v.cbegin());
			VERIFY(it == v.begin());
			VERIFY(it->first == Key{3});
			//VERIFY(it->second == T{10});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 5);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 2);
		{
			auto it = v.erase(v.cbegin() + 2);
			VERIFY(it == v.begin() + 2);
			VERIFY(it->first == Key{2});
			//VERIFY(it->second == T{10});
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 2);
		{
			auto it = v.erase(v.cbegin() + 3);
			VERIFY(it == v.end());
		}
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 2);
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

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.erase(v.begin() + 1), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = ThrowOnEraseContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		KeyContainer   a{Key{1}, Key{2}, Key{3}, Key{4}};
		ValueContainer b{5, 6, 7, 8};
		Map v(hamon::sorted_equivalent, hamon::move(a), hamon::move(b));

		EXPECT_THROW(v.erase(v.cbegin() + 2), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultimapTest, ErasePositionTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		hamon::flat_multimap<int, char> fm =
		{
			{3, 'a'},
			{1, 'b'},
			{4, 'c'},
			{1, 'd'},
		};

		// イテレート中に要素削除をするような場合には、
		// 範囲for文は使用できない
		for (auto it = fm.begin(); it != fm.end();)
		{
			// 条件一致した要素を削除する
			if (it->first == 1)
			{
				// 削除された要素の次を指すイテレータが返される。
				it = fm.erase(it);
			}
			// 要素削除をしない場合に、イテレータを進める
			else
			{
				++it;
			}
		}

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":" << p.second << ", ";
		}
		EXPECT_EQ("3:a, 4:c, ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace erase_position_test

}	// namespace hamon_flat_multimap_test
