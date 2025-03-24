/**
 *	@file	unit_test_unordered_multiset_extract_key.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr node_type extract(const key_type& x);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multiset_test
{

namespace extract_key_test
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
	using NodeType = typename Set::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().extract(hamon::declval<Key const&>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	//static_assert( noexcept(hamon::declval<Set&>().extract(hamon::declval<Key const&>())), "");
#endif

	Set v
	{
		Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, Key{4}, Key{4},
	};
	VERIFY(v.size() == 7);
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 2);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 3);
	VERIFY(v.count(Key{5}) == 1);

	{
		auto r = v.extract(Key{0});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{1});
		VERIFY(v.size() == 6);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{1});
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 3);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		auto r = v.extract(Key{4});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.value() == Key{4});
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 0);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
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

GTEST_TEST(UnorderedMultisetTest, ExtractKeyTest)
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

}	// namespace extract_key_test

}	// namespace hamon_unordered_multiset_test

#endif
