/**
 *	@file	unit_test_unordered_multimap_bucket_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr local_iterator begin(size_type n);
 *	constexpr const_local_iterator begin(size_type n) const;
 *	constexpr local_iterator end(size_type n);
 *	constexpr const_local_iterator end(size_type n) const;
 *	constexpr const_local_iterator cbegin(size_type n) const;
 *	constexpr const_local_iterator cend(size_type n) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace bucket_begin_end_test
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
	using SizeType = typename Map::size_type;
	using LocalIterator = typename Map::local_iterator;
	using ConstLocalIterator = typename Map::const_local_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().begin (hamon::declval<SizeType>())), LocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().end   (hamon::declval<SizeType>())), LocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().cbegin(hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().cend  (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().begin (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().end   (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().cbegin(hamon::declval<SizeType>())), ConstLocalIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().cend  (hamon::declval<SizeType>())), ConstLocalIterator>::value, "");

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	static_assert( noexcept(hamon::declval<Map&>().begin (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map&>().end   (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map&>().cbegin(hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map&>().cend  (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map const&>().begin (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map const&>().end   (hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map const&>().cbegin(hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map const&>().cend  (hamon::declval<SizeType>())), "");
#endif

	{
		auto check = [](LocalIterator it)
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

		for (SizeType i = 0; i < v.bucket_count(); ++i)
		{
			for (auto it = v.begin(i); it != v.end(i); ++it)
			{
				VERIFY(check(it));
			}
		}
	}
	{
		auto check = [](ConstLocalIterator it)
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

		for (SizeType i = 0; i < v.bucket_count(); ++i)
		{
			for (auto it = v.begin(i); it != v.end(i); ++it)
			{
				VERIFY(check(it));
			}
		}
	}
	{
		auto check = [](ConstLocalIterator it)
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

		for (SizeType i = 0; i < v.bucket_count(); ++i)
		{
			for (auto it = v.cbegin(i); it != v.cend(i); ++it)
			{
				VERIFY(check(it));
			}
		}
	}
	
	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, BucketBeginEndTest)
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

}	// namespace bucket_begin_end_test

}	// namespace hamon_unordered_multimap_test
