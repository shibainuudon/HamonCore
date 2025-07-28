/**
 *	@file	unit_test_flat_multiset_ctor_copy_alloc.cpp
 *
 *	@brief	コピーとアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr flat_multiset(const flat_multiset&, const Alloc& a);
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace ctor_copy_alloc_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, Set const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Set const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, Set const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Set const&, Alloc const&>::value, "");

	{
		Set const v1
		{
			Key{1},
			Key{3},
			Key{2},
		};
		Alloc const alloc;
		Set v2(v1, alloc);
		VERIFY(check_invariant(v2));
		VERIFY(v2.size() == 3);
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, CtorCopyAllocTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_copy_alloc_test

}	// namespace hamon_flat_multiset_test
