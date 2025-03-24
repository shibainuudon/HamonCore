/**
 *	@file	unit_test_unordered_map_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using key_type             = Key;
 *	using mapped_type          = T;
 *	using value_type           = pair<const Key, T>;
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

#include <hamon/unordered_map/unordered_map.hpp>
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
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace types_test
{

template <typename Key, typename T, typename Hash, typename Pred, template <typename> class TAllocator>
void test()
{
	using Allocator = TAllocator<typename hamon::unordered_map<Key, T, Hash, Pred>::value_type>;
	using Map = hamon::unordered_map<Key, T, Hash, Pred, Allocator>;

	using AllocTraits = hamon::allocator_traits<Allocator>;

	static_assert(hamon::is_same<typename Map::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Map::mapped_type, T>::value, "");
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	static_assert(hamon::is_same<typename Map::value_type, std::pair<const Key, T>>::value, "");
#else
	static_assert(hamon::is_same<typename Map::value_type, hamon::pair<const Key, T>>::value, "");
#endif
	static_assert(hamon::is_same<typename Map::hasher, Hash>::value, "");
	static_assert(hamon::is_same<typename Map::key_equal, Pred>::value, "");
	static_assert(hamon::is_same<typename Map::allocator_type, Allocator>::value, "");
	static_assert(hamon::is_same<typename Map::pointer, typename AllocTraits::pointer>::value, "");
	static_assert(hamon::is_same<typename Map::const_pointer, typename AllocTraits::const_pointer>::value, "");
	static_assert(hamon::is_same<typename Map::reference, typename Map::value_type&>::value, "");
	static_assert(hamon::is_same<typename Map::const_reference, const typename Map::value_type&>::value, "");
	static_assert(hamon::is_integral<typename Map::size_type>::value, "");
	static_assert(hamon::is_unsigned<typename Map::size_type>::value, "");
	static_assert(hamon::is_integral<typename Map::difference_type>::value, "");
	static_assert(hamon::is_signed<typename Map::difference_type>::value, "");
	static_assert(hamon::is_object<typename Map::iterator>::value, "");
	static_assert(hamon::is_object<typename Map::const_iterator>::value, "");
	static_assert(hamon::is_object<typename Map::local_iterator>::value, "");
	static_assert(hamon::is_object<typename Map::const_local_iterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))
	static_assert(hamon::is_object<typename Map::node_type>::value, "");
	static_assert(hamon::is_object<typename Map::insert_return_type>::value, "");
#endif
}

GTEST_TEST(UnorderedMapTest, TypesTest)
{
	test<int, char, hamon::hash<int>, hamon::equal_to<int>, hamon::allocator>();
	test<char, float, hamon::hash<char>, hamon::equal_to<>, hamon::allocator>();
	test<float, int, TransparentHash, hamon::equal_to<>, std::allocator>();
}

}	// namespace types_test

}	// namespace hamon_unordered_map_test
