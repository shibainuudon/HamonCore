/**
 *	@file	unit_test_multimap_iterator.cpp
 *
 *	@brief	iterator のテスト
 *
 *	using iterator               = implementation-defined; // see [container.requirements]
 *	using const_iterator         = implementation-defined; // see [container.requirements]
 *	using reverse_iterator       = std::reverse_iterator<iterator>;
 *	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/iterator.hpp>
#include <hamon/utility.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace iterator_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

template <typename T, typename U = T, typename = void>
struct has_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_eq<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_neq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_neq<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_lt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lt<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_lteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lteq<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_gt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gt<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U = T, typename = void>
struct has_gteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gteq<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U = T, typename = void>
struct has_compare_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_compare_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test_impl()
{
	using Map = hamon::multimap<Key, T>;
	using value_type      = typename Map::value_type;
	using difference_type = typename Map::difference_type;
	using iterator        = typename Map::iterator;
	using const_iterator  = typename Map::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<iterator>>::value, "");
	static_assert(hamon::is_same<value_type&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type const*>::value, "");
	static_assert(hamon::is_same<value_type&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<value_type*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(--hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() == (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() != (hamon::declval<iterator const&>()))>::value, "");

	static_assert( has_eq  <iterator const&, iterator const&>::value,"");
	static_assert( has_neq <iterator const&, iterator const&>::value,"");
	static_assert(!has_lt  <iterator const&, iterator const&>::value,"");
	static_assert(!has_lteq<iterator const&, iterator const&>::value,"");
	static_assert(!has_gt  <iterator const&, iterator const&>::value,"");
	static_assert(!has_gteq<iterator const&, iterator const&>::value,"");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<iterator const&, iterator const&>::value,"");
#endif

	static_assert( hamon::detail::cpp17_input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert( hamon::input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<value_type const&, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<const_iterator>>::value, "");
	static_assert(hamon::is_default_constructible<const_iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<const_iterator>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type const*>::value, "");
	static_assert(hamon::is_same<value_type const&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<value_type const*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(--hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() == (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() != (hamon::declval<const_iterator const&>()))>::value, "");

	static_assert( has_eq  <const_iterator const&, const_iterator const&>::value,"");
	static_assert( has_neq <const_iterator const&, const_iterator const&>::value,"");
	static_assert(!has_lt  <const_iterator const&, const_iterator const&>::value,"");
	static_assert(!has_lteq<const_iterator const&, const_iterator const&>::value,"");
	static_assert(!has_gt  <const_iterator const&, const_iterator const&>::value,"");
	static_assert(!has_gteq<const_iterator const&, const_iterator const&>::value,"");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<const_iterator const&, const_iterator const&>::value,"");
#endif

	static_assert( has_eq <iterator const&, const_iterator const&>::value,"");
	static_assert( has_eq <const_iterator const&, iterator const&>::value,"");
	static_assert( has_neq<iterator const&, const_iterator const&>::value,"");
	static_assert( has_neq<const_iterator const&, iterator const&>::value,"");

	static_assert( hamon::is_constructible<iterator,       iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator,       const_iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, const_iterator>::value, "");

	return true;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<Key, char>());
	VERIFY(test_impl<Key, short>());
	VERIFY(test_impl<Key, int>());
	VERIFY(test_impl<Key, long>());
	VERIFY(test_impl<Key, float>());

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, IteratorTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<short>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<long>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace iterator_test

}	// namespace hamon_multimap_test
