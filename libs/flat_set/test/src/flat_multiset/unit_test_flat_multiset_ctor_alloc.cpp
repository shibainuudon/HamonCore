/**
 *	@file	unit_test_flat_multiset_ctor_alloc.cpp
 *
 *	@brief	アロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr explicit flat_multiset(const Alloc& a);
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

namespace ctor_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;
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

GTEST_TEST(FlatMultisetTest, CtorAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, hamon::less<>>()));
}

}	// namespace ctor_alloc_test

}	// namespace hamon_flat_multiset_test
