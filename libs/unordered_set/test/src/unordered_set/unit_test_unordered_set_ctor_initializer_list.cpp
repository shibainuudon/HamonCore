/**
 *	@file	unit_test_unordered_set_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_set(
 *		initializer_list<value_type> il,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	constexpr unordered_set(
 *		initializer_list<value_type> il,
 *		size_type n,
 *		const allocator_type& a)
 *
 *	constexpr unordered_set(
 *		initializer_list<value_type> il,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace ctor_initializer_list_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using SizeType  = typename Set::size_type;
	using Hasher    = typename Set::hasher;
	using KeyEqual  = typename Set::key_equal;
	using Allocator = typename Set::allocator_type;
	using ValueType = typename Set::value_type;

	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

	// (il)
	{
		Set v { Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3}, };
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n)
	{
		Set v
		{
			{ Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, },
			3
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n, hf)
	{
		Set v
		{
			{ Key{3}, Key{1}, Key{4}, Key{1}, Key{5}, Key{2}, },
			5, Hasher{}
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n, hf, eql)
	{
		Set v
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			10, Hasher{}, KeyEqual{}
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 10);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n, hf, eql, a)
	{
		Allocator alloc;
		Set v
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			2, Hasher{}, KeyEqual{}, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 2);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}

#if !(defined(HAMON_USE_STD_UNORDERED_SET) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");

	// (il, n, a)
	{
		Allocator alloc;
		Set v
		{
			{ Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3}, },
			8, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 8);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
	// (il, n, hf, a)
	{
		Allocator alloc;
		Set v
		{
			{ Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3}, },
			16, Hasher{}, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 16);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

#if !defined(HAMON_USE_STD_UNORDERED_SET)	// TODO(LWG 2713)
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, Allocator const&>::value, "");

	// (il, a)
	{
		Allocator alloc;
		Set v
		{
			{ Key{2}, Key{3}, Key{1}, Key{1}, Key{2}, Key{3}, },
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, CtorInitializerListTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace ctor_initializer_list_test

}	// namespace hamon_unordered_set_test
