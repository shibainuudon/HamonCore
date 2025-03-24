/**
 *	@file	unit_test_unordered_multimap_begin_end.cpp
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

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
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
				VERIFY(it->second == 30 || it->second == 40);
			}
			else if (it->first == 2)
			{
				VERIFY(it->second == 10 || it->second == 50);
			}
			else if (it->first == 3)
			{
				VERIFY(it->second == 20 || it->second == 60);
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

		it++;
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
				VERIFY(it->second == 30 || it->second == 40);
			}
			else if (it->first == 2)
			{
				VERIFY(it->second == 10 || it->second == 50);
			}
			else if (it->first == 3)
			{
				VERIFY(it->second == 20 || it->second == 60);
			}
			else
			{
				VERIFY(false);
			}
			return true;
		};

		Map const v
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

		it++;
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

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, BeginEndTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_unordered_multimap_test
