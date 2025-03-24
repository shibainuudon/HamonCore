/**
 *	@file	unit_test_unordered_map_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator       begin() noexcept;
 *	constexpr const_iterator begin() const noexcept;
 *	constexpr iterator       end() noexcept;
 *	constexpr const_iterator end() const noexcept;
 *	constexpr const_iterator cbegin() const noexcept;
 *	constexpr const_iterator cend() const noexcept;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
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
		auto check = [](Iterator it)
		{
			if (it->first == 1)
			{
				VERIFY(it->second == 30);
			}
			else if (it->first == 2)
			{
				VERIFY(it->second == 10);
			}
			else if (it->first == 3)
			{
				VERIFY(it->second == 20);
			}
			else
			{
				VERIFY(false);
			}
			return true;
		};

		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		it++;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		auto check = [](ConstIterator it)
		{
			if (it->first == 1)
			{
				VERIFY(it->second == 10);
			}
			else if (it->first == 2)
			{
				VERIFY(it->second == 20);
			}
			else
			{
				VERIFY(false);
			}
			return true;
		};

		Map const v
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
		};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(check(it));

		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, BeginEndTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_unordered_map_test
