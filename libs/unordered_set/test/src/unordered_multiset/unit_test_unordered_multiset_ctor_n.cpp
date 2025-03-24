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
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace ctor_n_test
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
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Set, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

	// (n)
	{
		Set v(10);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 10);
	}
	// (n, hf)
	{
		Set v{8, Hasher{}};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 8);
	}
	// (n, hf, eql)
	{
		Set v{17, Hasher{}, KeyEqual{}};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 17);
	}
	// (n, hf, eql, a)
	{
		Allocator alloc;
		Set v{3, Hasher{}, KeyEqual{}, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.get_allocator() == alloc);
	}

#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, SizeType, Hasher const&, Allocator const&>::value, "");

	// (n, a)
	{
		Allocator alloc;
		Set v{4, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 4);
		VERIFY(v.get_allocator() == alloc);
	}
	// (n, hf, a)
	{
		Allocator alloc;
		Set v{1, Hasher{}, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.get_allocator() == alloc);
	}
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
