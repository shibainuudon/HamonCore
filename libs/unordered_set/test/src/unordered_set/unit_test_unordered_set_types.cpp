﻿/**
 *	@file	unit_test_unordered_set_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using key_type             = Key;
 *	using value_type           = Key;
 *	using hasher               = Hash;
 *	using key_equal            = Pred;
 *	using allocator_type       = Allocator;
 *	using pointer              = typename allocator_traits<Allocator>::pointer;
 *	using const_pointer        = typename allocator_traits<Allocator>::const_pointer;
 *	using reference            = value_type&;
 *	using const_reference      = const value_type&;
 *	using size_type            = implementation-defined; // see [container.requirements]
 *	using difference_type      = implementation-defined; // see [container.requirements]
 *
 *	using iterator             = implementation-defined; // see [container.requirements]
 *	using const_iterator       = implementation-defined; // see [container.requirements]
 *	using local_iterator       = implementation-defined; // see [container.requirements]
 *	using const_local_iterator = implementation-defined; // see [container.requirements]
 *	using node_type            = unspecified;
 *	using insert_return_type   = insert-return-type<iterator, node_type>;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace types_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Hash, typename Pred, typename Allocator>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key, Hash, Pred, Allocator>;

	using AllocTraits = hamon::allocator_traits<Allocator>;

	static_assert(hamon::is_same<typename Set::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Set::value_type, Key>::value, "");
	static_assert(hamon::is_same<typename Set::hasher, Hash>::value, "");
	static_assert(hamon::is_same<typename Set::key_equal, Pred>::value, "");
	static_assert(hamon::is_same<typename Set::allocator_type, Allocator>::value, "");
	static_assert(hamon::is_same<typename Set::pointer, typename AllocTraits::pointer>::value, "");
	static_assert(hamon::is_same<typename Set::const_pointer, typename AllocTraits::const_pointer>::value, "");
	static_assert(hamon::is_same<typename Set::reference, typename Set::value_type&>::value, "");
	static_assert(hamon::is_same<typename Set::const_reference, const typename Set::value_type&>::value, "");
	static_assert(hamon::is_integral<typename Set::size_type>::value, "");
	static_assert(hamon::is_unsigned<typename Set::size_type>::value, "");
	static_assert(hamon::is_integral<typename Set::difference_type>::value, "");
	static_assert(hamon::is_signed<typename Set::difference_type>::value, "");
	static_assert(hamon::is_object<typename Set::iterator>::value, "");
	static_assert(hamon::is_object<typename Set::const_iterator>::value, "");
	static_assert(hamon::is_object<typename Set::local_iterator>::value, "");
	static_assert(hamon::is_object<typename Set::const_local_iterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))
	static_assert(hamon::is_object<typename Set::node_type>::value, "");
	static_assert(hamon::is_object<typename Set::insert_return_type>::value, "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, TypesTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int, hamon::hash<int>, hamon::equal_to<int>, hamon::allocator<int>>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char, hamon::hash<char>, hamon::equal_to<>, hamon::allocator<char>>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float, decltype(hamon::ranges::hash), hamon::equal_to<>, hamon::allocator<float>>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace types_test

}	// namespace hamon_unordered_set_test
