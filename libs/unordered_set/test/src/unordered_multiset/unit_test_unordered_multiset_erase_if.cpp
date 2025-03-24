/**
 *	@file	unit_test_unordered_multiset_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class K, class T, class H, class P, class A, class Predicate>
 *	constexpr typename unordered_multiset<K, T, H, P, A>::size_type
 *	erase_if(unordered_multiset<K, T, H, P, A>& c, Predicate pred);
 */

#include <hamon/unordered_set/erase_if.hpp>
#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace erase_if_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct is_key_1
{
	template <typename T>
	constexpr bool operator()(T const& x) const
	{
		return x == 1;
	}
};

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::erase_if(hamon::declval<Set&>(), hamon::declval<is_key_1>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Set&>(), hamon::declval<is_key_1>())), "");

	{
		Set v
		{
			Key{1}, Key{1}, Key{2}, Key{3}, Key{3}, Key{3}, Key{4}, Key{4},
		};

		auto r = hamon::erase_if(v, is_key_1{});
		VERIFY(r == 2);

		VERIFY(v.size() == 6);
		VERIFY(v.count(Key{1}) == 0);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 2);
	}
	{
		Set v
		{
			Key{1}, Key{1}, Key{2}, Key{3}, Key{3}, Key{3}, Key{4}, Key{4},
		};

		auto r = hamon::erase_if(v, [](Key const& x){return x > 2;});
		VERIFY(r == 5);

		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, EraseIfTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace erase_if_test

}	// namespace hamon_unordered_multiset_test
