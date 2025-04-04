/**
 *	@file	unit_test_unordered_multiset_ctor_n.cpp
 *
 *	@brief	バケット数を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit unordered_multiset(
 *		size_type n,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	constexpr unordered_multiset(size_type n, const allocator_type& a)
 *		: unordered_multiset(n, hasher(), key_equal(), a) { }
 *
 *	constexpr unordered_multiset(size_type n, const hasher& hf, const allocator_type& a)
 *		: unordered_multiset(n, hf, key_equal(), a) { }
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace ctor_n_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
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
	using SizeType  = typename Set::size_type;
	using Hasher    = typename Set::hasher;
	using KeyEqual  = typename Set::key_equal;
	using Allocator = typename Set::allocator_type;

	static_assert( hamon::is_constructible<Set, SizeType>::value, "");
	static_assert( hamon::is_constructible<Set, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Set, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Set, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Set, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CtorNTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctor_n_test

}	// namespace hamon_unordered_multiset_test
