/**
 *	@file	unit_test_deque_types.cpp
 *
 *	@brief	types のテスト
 *
 *	// types
 *	using value_type             = T;
 *	using allocator_type         = Allocator;
 *	using pointer                = typename allocator_traits<Allocator>::pointer;
 *	using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
 *	using reference              = value_type&;
 *	using const_reference        = const value_type&;
 *	using size_type              = implementation-defined; // see [container.requirements]
 *	using difference_type        = implementation-defined; // see [container.requirements]
 *	using iterator               = implementation-defined; // see [container.requirements]
 *	using const_iterator         = implementation-defined; // see [container.requirements]
 *	using reverse_iterator       = std::reverse_iterator<iterator>;
 *	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace types_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Allocator = std::allocator<T>;
	using Deque = hamon::deque<T, Allocator>;
	using value_type      = typename Deque::value_type;
	using allocator_type  = typename Deque::allocator_type;
	using pointer         = typename Deque::pointer;
	using const_pointer   = typename Deque::const_pointer;
	using reference       = typename Deque::reference;
	using const_reference = typename Deque::const_reference;
	using size_type       = typename Deque::size_type;
	using difference_type = typename Deque::difference_type;
	using iterator        = typename Deque::iterator;
	using const_iterator  = typename Deque::const_iterator;

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
	static_assert(hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<value_type&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<value_type const&, hamon::iter_reference_t<const_iterator>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, TypesTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace types_test

}	// namespace hamon_deque_test
