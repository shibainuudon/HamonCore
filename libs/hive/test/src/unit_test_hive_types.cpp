/**
 *	@file	unit_test_hive_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using value_type = T;
 *	using allocator_type = Allocator;
 *	using pointer = typename allocator_traits<Allocator>::pointer;
 *	using const_pointer = typename allocator_traits<Allocator>::const_pointer;
 *	using reference = value_type&;
 *	using const_reference = const value_type&;
 *	using size_type = implementation-defined;                               // see [container.requirements]
 *	using difference_type = implementation-defined;                         // see [container.requirements]
 *	using iterator = implementation-defined;                                // see [container.requirements]
 *	using const_iterator = implementation-defined;                          // see [container.requirements]
 *	using reverse_iterator = std::reverse_iterator<iterator>;               // see [container.requirements]
 *	using const_reverse_iterator = std::reverse_iterator<const_iterator>;   // see [container.requirements]
 */

#include <hamon/hive.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace types_test
{

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = hamon::allocator<T>;
	using Hive = hamon::hive<T, Allocator>;

	using value_type              = typename Hive::value_type;
	using allocator_type          = typename Hive::allocator_type;
	using pointer                 = typename Hive::pointer;
	using const_pointer           = typename Hive::const_pointer;
	using reference               = typename Hive::reference;
	using const_reference         = typename Hive::const_reference;
	using size_type               = typename Hive::size_type;
	using difference_type         = typename Hive::difference_type;
	using iterator                = typename Hive::iterator;
	using const_iterator          = typename Hive::const_iterator;
	using reverse_iterator        = typename Hive::reverse_iterator;
	using const_reverse_iterator  = typename Hive::const_reverse_iterator;

	static_assert(hamon::is_same<value_type,      T>::value, "");
	static_assert(hamon::is_same<allocator_type,  Allocator>::value, "");
	static_assert(hamon::is_same<pointer,         T*>::value, "");
	static_assert(hamon::is_same<const_pointer,   T const*>::value, "");
	static_assert(hamon::is_same<reference,       T&>::value, "");
	static_assert(hamon::is_same<const_reference, T const&>::value, "");
	static_assert(hamon::is_unsigned<size_type>::value, "");
	static_assert(hamon::is_integral<size_type>::value, "");
	static_assert(hamon::is_signed<difference_type>::value, "");
	static_assert(hamon::is_integral<difference_type>::value, "");
	static_assert(hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(hamon::detail::cpp17_bidirectional_iterator_t<reverse_iterator>::value, "");
	static_assert(hamon::detail::cpp17_bidirectional_iterator_t<const_reverse_iterator>::value, "");

	return true;
}

GTEST_TEST(HiveTest, TypesTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace types_test

}	// namespace hamon_hive_test
