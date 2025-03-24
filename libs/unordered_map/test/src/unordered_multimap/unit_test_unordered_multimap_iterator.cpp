/**
 *	@file	unit_test_unordered_multimap_iterator.cpp
 *
 *	@brief	iterator のテスト
 *
 *	using iterator             = implementation-defined; // see [container.requirements]
 *	using const_iterator       = implementation-defined; // see [container.requirements]
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/detail/cpp17_forward_iterator.hpp>
#include <hamon/iterator/detail/cpp17_bidirectional_iterator.hpp>
#include <hamon/iterator/detail/cpp17_random_access_iterator.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace iterator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using value_type      = typename Map::value_type;
	using difference_type = typename Map::difference_type;
	using iterator        = typename Map::iterator;
	using const_iterator  = typename Map::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
//	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
//	static_assert(!hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<iterator>>::value, "");
	static_assert(hamon::is_same<value_type&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
//	static_assert(!hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type const*>::value, "");
	static_assert(hamon::is_same<value_type&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<value_type*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
	//static_assert(hamon::is_same<iterator&, decltype(--hamon::declval<iterator&>())>::value, "");
	//static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()--)>::value, "");
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
//	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert( hamon::input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::forward_iterator_t<const_iterator>::value, "");
//	static_assert(!hamon::bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<value_type const&, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<const_iterator>>::value, "");
	static_assert(hamon::is_default_constructible<const_iterator>::value, "");
//	static_assert(!hamon::is_nothrow_default_constructible<const_iterator>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type const*>::value, "");
	static_assert(hamon::is_same<value_type const&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<value_type const*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
	//static_assert(hamon::is_same<const_iterator&, decltype(--hamon::declval<const_iterator&>())>::value, "");
	//static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()--)>::value, "");
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

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, IteratorTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace iterator_test

}	// namespace hamon_unordered_multimap_test
