/**
 *	@file	unit_test_unordered_multiset_erase_key.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr size_type erase(const key_type& k);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace erase_key_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");
#endif

	{
		Set v{Key{2}, Key{2}, Key{7}, Key{8}, Key{6}, Key{5}, Key{5}, Key{1}, Key{7}, Key{7}};
		VERIFY(v.size() == 10);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{0});
			VERIFY(r == 0);
		}
		VERIFY(v.size() == 10);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{1});
			VERIFY(r == 1);
		}
		VERIFY(v.size() == 9);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{2});
			VERIFY(r == 2);
		}
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{3});
			VERIFY(r == 0);
		}
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{4});
			VERIFY(r == 0);
		}
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 2);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{5});
			VERIFY(r == 2);
		}
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		VERIFY(v.count(Key{6}) == 1);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{6});
			VERIFY(r == 1);
		}
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		VERIFY(v.count(Key{6}) == 0);
		VERIFY(v.count(Key{7}) == 3);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{7});
			VERIFY(r == 3);
		}
		VERIFY(v.size() == 1);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		VERIFY(v.count(Key{6}) == 0);
		VERIFY(v.count(Key{7}) == 0);
		VERIFY(v.count(Key{8}) == 1);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{8});
			VERIFY(r == 1);
		}
		VERIFY(v.size() == 0);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		VERIFY(v.count(Key{6}) == 0);
		VERIFY(v.count(Key{7}) == 0);
		VERIFY(v.count(Key{8}) == 0);
		VERIFY(v.count(Key{9}) == 0);

		{
			auto r = v.erase(Key{9});
			VERIFY(r == 0);
		}
		VERIFY(v.size() == 0);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);
		VERIFY(v.count(Key{6}) == 0);
		VERIFY(v.count(Key{7}) == 0);
		VERIFY(v.count(Key{8}) == 0);
		VERIFY(v.count(Key{9}) == 0);
	}

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, EraseKeyTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace erase_key_test

}	// namespace hamon_unordered_multiset_test
