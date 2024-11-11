/**
 *	@file	unit_test_set_node_type.cpp
 *
 *	@brief	node_type のテスト
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_set_test
{

namespace node_type_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
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
#if !defined(HAMON_USE_STD_SET)
	static_assert(!hamon::is_nothrow_move_assignable<NodeType>::value, "");
#endif
	static_assert(!hamon::is_trivially_move_assignable<NodeType>::value, "");

	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().operator bool()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().get_allocator()), AllocType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType const&>().value()), Key&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<NodeType&>().swap(hamon::declval<NodeType&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<NodeType&>(), hamon::declval<NodeType&>())), void>::value, "");

#if !defined(HAMON_USE_STD_SET)
	static_assert( noexcept(hamon::declval<NodeType const&>().empty()), "");
	static_assert( noexcept(hamon::declval<NodeType const&>().operator bool()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().get_allocator()), "");
	static_assert(!noexcept(hamon::declval<NodeType const&>().value()), "");
	static_assert( noexcept(hamon::declval<NodeType&>().swap(hamon::declval<NodeType&>())), "");
	static_assert( noexcept(swap(hamon::declval<NodeType&>(), hamon::declval<NodeType&>())), "");
#endif

	{
		NodeType node;
		VERIFY(node.empty());
		VERIFY(bool(node) == false);
	}
	{
		Set s
		{
			Key{3},
			Key{1},
		};
		NodeType n1 = s.extract(Key{1});
		NodeType n2 = s.extract(Key{2});
		NodeType n3 = s.extract(Key{3});

		VERIFY(!n1.empty());
		VERIFY( n2.empty());
		VERIFY(!n3.empty());

		VERIFY(bool(n1) == true);
		VERIFY(bool(n2) == false);
		VERIFY(bool(n3) == true);

		VERIFY(n1.value() == Key{1});
		VERIFY(n3.value() == Key{3});

#if !defined(HAMON_MSVC)	// MSVC だと constexpr にできない
		VERIFY(n1.get_allocator() == s.get_allocator());
		VERIFY(n3.get_allocator() == s.get_allocator());
#endif

		n1.value() = Key{2};

		n1.swap(n3);

		VERIFY(n1.value() == Key{3});
		VERIFY(n3.value() == Key{2});

		swap(n1, n3);

		VERIFY(n1.value() == Key{2});
		VERIFY(n3.value() == Key{3});

#if !defined(HAMON_MSVC)	// MSVC だと constexpr にできない
		n1.swap(n2);

		VERIFY( n1.empty());
		VERIFY(!n2.empty());
		VERIFY(!n3.empty());

		VERIFY(n2.value() == Key{2});
		VERIFY(n3.value() == Key{3});

		VERIFY(n2.get_allocator() == s.get_allocator());
		VERIFY(n3.get_allocator() == s.get_allocator());
#endif
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, NodeTypeTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace node_type_test

}	// namespace hamon_set_test

#endif
