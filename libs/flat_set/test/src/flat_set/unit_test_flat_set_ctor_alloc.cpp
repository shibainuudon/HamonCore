/**
 *	@file	unit_test_flat_set_ctor_alloc.cpp
 *
 *	@brief	アロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr explicit flat_set(const Alloc& a);
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace ctor_alloc_test
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
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Set, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Alloc const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Alloc const&>::value, "");

	{
		Alloc const alloc;
		Set v{alloc};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, CtorAllocTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_alloc_test

}	// namespace hamon_flat_set_test
