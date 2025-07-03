/**
 *	@file	unit_test_flat_multimap_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator               begin() noexcept;
 *	constexpr const_iterator         begin() const noexcept;
 *	constexpr iterator               end() noexcept;
 *	constexpr const_iterator         end() const noexcept;
 *	constexpr const_iterator         cbegin() const noexcept;
 *	constexpr const_iterator         cend() const noexcept;
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
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace begin_end_test
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
	using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().begin()),   Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().end()),     Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().cbegin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().cend()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().begin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().end()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().cbegin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().cend()),   ConstIterator>::value, "");

	static_assert(noexcept(hamon::declval<Map&>().begin()), "");
	static_assert(noexcept(hamon::declval<Map&>().end()), "");
	static_assert(noexcept(hamon::declval<Map&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Map&>().cend()), "");
	static_assert(noexcept(hamon::declval<Map const&>().begin()), "");
	static_assert(noexcept(hamon::declval<Map const&>().end()), "");
	static_assert(noexcept(hamon::declval<Map const&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Map const&>().cend()), "");

	{
		Map v;
		{
			auto it = v.begin();
			VERIFY(it == v.begin());
			VERIFY(it == v.end());
		}
		{
			auto it = v.cbegin();
			VERIFY(it == v.cbegin());
			VERIFY(it == v.cend());
		}
		Map const cv;
		{
			auto it = cv.begin();
			VERIFY(it == cv.begin());
			VERIFY(it == cv.end());
		}
		{
			auto it = cv.cbegin();
			VERIFY(it == cv.cbegin());
			VERIFY(it == cv.cend());
		}
	}
	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{30});
		{
			auto t = ++it;
			VERIFY(t->first == Key{2});
			VERIFY(t->second == T{10});
		}
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it->first == Key{2});
		VERIFY(it->second == T{10});
		{
			auto t = it++;
			VERIFY(t->first == Key{2});
			VERIFY(t->second == T{10});
		}
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY((*it).first == Key{3});
		VERIFY((*it).second == T{20});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		Map const v
		{
			{Key{4}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{1}, T{40}},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{40});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY((*it).first == Key{2});
		VERIFY((*it).second == T{20});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{30});
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{10});
		it++;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, BeginEndTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	{
		hamon::flat_multimap<int, char> fm =
		{
			{10, 'A'}, {11, 'B'}, {12, 'C'},
			{10, 'a'}, {11, 'b'}, {12, 'c'},
		};

		{
			auto i = fm.begin();
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'A');
			++i;
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'a');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'B');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'b');
			++i;
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'C');
			++i;
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'c');
			++i;
			EXPECT_TRUE(i == fm.end());
		}
		{
			auto i = fm.cbegin();
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'A');
			++i;
			EXPECT_TRUE(i->first == 10);
			EXPECT_TRUE(i->second == 'a');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'B');
			++i;
			EXPECT_TRUE(i->first == 11);
			EXPECT_TRUE(i->second == 'b');
			++i;
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'C');
			++i;
			EXPECT_TRUE(i->first == 12);
			EXPECT_TRUE(i->second == 'c');
			++i;
			EXPECT_TRUE(i == fm.cend());
		}
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_flat_multimap_test
