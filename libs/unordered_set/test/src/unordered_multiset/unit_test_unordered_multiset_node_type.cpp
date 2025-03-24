/**
 *	@file	unit_test_unordered_multiset_node_type.cpp
 *
 *	@brief	node_type のテスト
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multiset_test
{

namespace node_type_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Hash, typename Pred>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key, Hash, Pred>;

	using NodeType = typename Set::node_type;
	using AllocType = typename Set::allocator_type;

	static_assert(hamon::is_same<typename NodeType::value_type, Key>::value, "");
	static_assert(hamon::is_same<typename NodeType::allocator_type, AllocType>::value, "");

	static_assert( hamon::is_default_constructible<NodeType>::value, "");
	static_assert( hamon::is_nothrow_default_constructible<NodeType>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<NodeType>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<NodeType>::value, "");

	static_assert(!hamon::is_copy_constructible<NodeType>::value, "");

	static_assert( hamon::is_move_constructible<NodeType>::value, "");
	static_assert( hamon::is_nothrow_move_constructible<NodeType>::value, "");
	static_assert(!hamon::is_trivially_move_constructible<NodeType>::value, "");
	static_assert( hamon::is_implicitly_move_constructible<NodeType>::value, "");

	static_assert(!hamon::is_copy_assignable<NodeType>::value, "");

	static_assert( hamon::is_move_assignable<NodeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	static_assert(!hamon::is_nothrow_move_assignable<NodeType>::value, "");
#endif
	static_assert(!hamon::is_trivially_move_assignable<NodeType>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().operator bool()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().get_allocator()), AllocType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().value()), Key&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType&>().swap(hamon::declval<NodeType&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<NodeType&>(), hamon::declval<NodeType&>())), void>::value, "");

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	static_assert( noexcept(hamon::declval<NodeType const&>().empty()), "");
	static_assert( noexcept(hamon::declval<NodeType const&>().operator bool()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().get_allocator()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().value()), "");
	static_assert( noexcept(hamon::declval<NodeType&>().swap(hamon::declval<NodeType&>())), "");
	static_assert( noexcept(swap(hamon::declval<NodeType&>(), hamon::declval<NodeType&>())), "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, NodeTypeTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int, hamon::hash<int>, hamon::equal_to<int>>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char, hamon::hash<char>, hamon::equal_to<>>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float, decltype(hamon::ranges::hash), hamon::equal_to<>>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace node_type_test

}	// namespace hamon_unordered_multiset_test

#endif
