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
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace ctor_initializer_list_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET)
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

#if !(defined(HAMON_USE_STD_UNORDERED_SET) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
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
