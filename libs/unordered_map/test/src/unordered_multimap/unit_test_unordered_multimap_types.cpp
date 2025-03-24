/**
 *	@file	unit_test_unordered_multimap_types.cpp
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
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace types_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, typename Hash, typename Pred, typename Allocator>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T, Hash, Pred, Allocator>;

	using AllocTraits = hamon::allocator_traits<Allocator>;

	static_assert(hamon::is_same<typename Map::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Map::mapped_type, T>::value, "");
#if defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
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
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))
	static_assert(hamon::is_object<typename Map::node_type>::value, "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, TypesTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char, hamon::hash<int>, hamon::equal_to<int>, hamon::allocator<std::pair<const int, char>>>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float, hamon::hash<char>, hamon::equal_to<>, hamon::allocator<std::pair<const char, float>>>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int, decltype(hamon::ranges::hash), hamon::equal_to<>, hamon::allocator<std::pair<const float, int>>>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace types_test

}	// namespace hamon_unordered_multimap_test
