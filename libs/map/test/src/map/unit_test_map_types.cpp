/**
 *	@file	unit_test_map_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using key_type               = Key;
 *	using mapped_type            = T;
 *	using value_type             = pair<const Key, T>;
 *	using key_compare            = Compare;
 *	using allocator_type         = Allocator;
 *	using pointer                = typename allocator_traits<Allocator>::pointer;
 *	using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
 *	using reference              = value_type&;
 *	using const_reference        = const value_type&;
 *	using size_type              = implementation-defined; // see [container.requirements]
 *	using difference_type        = implementation-defined; // see [container.requirements]
 *	using node_type              = unspecified;
 *	using insert_return_type     = insert-return-type<iterator, node_type>;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace types_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, typename Compare, template <typename> class TAllocator>
MAP_TEST_CONSTEXPR bool test()
{
	using Allocator = TAllocator<typename hamon::map<Key, T>::value_type>;
	using Map = hamon::map<Key, T, Compare, Allocator>;
	using AllocTraits = hamon::allocator_traits<Allocator>;

	static_assert(hamon::is_same<typename Map::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Map::mapped_type, T>::value, "");
#if !defined(HAMON_USE_STD_MAP)
	static_assert(hamon::is_same<typename Map::value_type, hamon::pair<const Key, T>>::value, "");
#endif
	static_assert(hamon::is_same<typename Map::key_compare, Compare>::value, "");
	static_assert(hamon::is_same<typename Map::allocator_type, Allocator>::value, "");
	static_assert(hamon::is_same<typename Map::pointer, typename AllocTraits::pointer>::value, "");
	static_assert(hamon::is_same<typename Map::const_pointer, typename AllocTraits::const_pointer>::value, "");
	static_assert(hamon::is_same<typename Map::reference, typename Map::value_type&>::value, "");
	static_assert(hamon::is_same<typename Map::const_reference, const typename Map::value_type&>::value, "");
	static_assert(hamon::is_integral<typename Map::size_type>::value, "");
	static_assert(hamon::is_unsigned<typename Map::size_type>::value, "");
	static_assert(hamon::is_integral<typename Map::difference_type>::value, "");
	static_assert(hamon::is_signed<typename Map::difference_type>::value, "");
#if !defined(HAMON_USE_STD_MAP)
	static_assert(hamon::is_object<typename Map::node_type>::value, "");
	static_assert(hamon::is_object<typename Map::insert_return_type>::value, "");
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, TypesTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char, hamon::less<int>, hamon::allocator>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float, hamon::less<>, std::allocator>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int, hamon::greater<>, hamon::allocator>()));
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace types_test

}	// namespace hamon_map_test
