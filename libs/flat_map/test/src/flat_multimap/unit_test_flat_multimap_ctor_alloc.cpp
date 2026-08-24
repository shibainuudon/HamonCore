/**
 *	@file	unit_test_flat_multimap_ctor_alloc.cpp
 *
 *	@brief	アロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr explicit flat_multimap(const Alloc& a);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_alloc_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Map, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Alloc const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Alloc const&>::value, "");

	{
		Alloc const alloc;
		Map v{alloc};
		VERIFY(check_invariant(v));
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, CtorAllocTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));
}

}	// namespace ctor_alloc_test

}	// namespace hamon_flat_multimap_test
