/**
 *	@file	unit_test_unordered_multiset_types.cpp
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
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <utility>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace types_test
{

template <typename Key, typename Hash, typename Pred, typename Allocator>
void test()
{
	using Set = hamon::unordered_multiset<Key, Hash, Pred, Allocator>;

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
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))
	static_assert(hamon::is_object<typename Set::node_type>::value, "");
#endif
}

GTEST_TEST(UnorderedMultisetTest, TypesTest)
{
	test<int, hamon::hash<int>, hamon::equal_to<int>, hamon::allocator<int>>();
	test<char, hamon::hash<char>, hamon::equal_to<>, hamon::allocator<char>>();
	test<float, TransparentHash, hamon::equal_to<>, hamon::allocator<float>>();
}

}	// namespace types_test

}	// namespace hamon_unordered_multiset_test
