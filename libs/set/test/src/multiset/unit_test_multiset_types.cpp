/**
 *	@file	unit_test_multiset_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using key_type               = Key;
 *	using key_compare            = Compare;
 *	using value_type             = Key;
 *	using value_compare          = Compare;
 *	using allocator_type         = Allocator;
 *	using pointer                = typename allocator_traits<Allocator>::pointer;
 *	using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
 *	using reference              = value_type&;
 *	using const_reference        = const value_type&;
 *	using size_type              = implementation-defined; // see [container.requirements]
 *	using difference_type        = implementation-defined; // see [container.requirements]
 *	using node_type              = unspecified;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace types_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Compare, typename Allocator>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::multiset<Key, Compare, Allocator>;
	using AllocTraits = hamon::allocator_traits<Allocator>;

	static_assert(hamon::is_same<typename Set::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Set::key_compare, Compare>::value, "");
	static_assert(hamon::is_same<typename Set::value_type, Key>::value, "");
	static_assert(hamon::is_same<typename Set::value_compare, Compare>::value, "");
	static_assert(hamon::is_same<typename Set::allocator_type, Allocator>::value, "");
	static_assert(hamon::is_same<typename Set::pointer, typename AllocTraits::pointer>::value, "");
	static_assert(hamon::is_same<typename Set::const_pointer, typename AllocTraits::const_pointer>::value, "");
	static_assert(hamon::is_same<typename Set::reference, Key&>::value, "");
	static_assert(hamon::is_same<typename Set::const_reference, const Key&>::value, "");
	static_assert(hamon::is_integral<typename Set::size_type>::value, "");
	static_assert(hamon::is_unsigned<typename Set::size_type>::value, "");
	static_assert(hamon::is_integral<typename Set::difference_type>::value, "");
	static_assert(hamon::is_signed<typename Set::difference_type>::value, "");
	static_assert(hamon::is_object<typename Set::node_type>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, TypesTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, hamon::less<int>, hamon::allocator<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, hamon::less<>, hamon::allocator<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, hamon::greater<>, hamon::allocator<float>>()));
}

}	// namespace types_test

}	// namespace hamon_multiset_test
