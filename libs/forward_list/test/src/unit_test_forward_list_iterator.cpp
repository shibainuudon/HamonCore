/**
 *	@file	unit_test_forward_list_iterator.cpp
 *
 *	@brief	forward_list<T>::iterator のテスト
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/iterator.hpp>
#include <hamon/utility.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_forward_list_test
{

namespace iterator_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;
	using difference_type = typename ForwardList::difference_type;
	using iterator      = typename ForwardList::iterator;
	using const_iterator = typename ForwardList::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert( hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
	static_assert(!hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<T, hamon::iter_value_t<iterator>>::value, "");
	static_assert(hamon::is_same<T&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, T*>::value, "");
	static_assert(!hamon::is_constructible<iterator, T const*>::value, "");
	static_assert(hamon::is_same<T&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<T*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
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
	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert( hamon::input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::forward_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<T, hamon::iter_value_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<T const&, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<const_iterator>>::value, "");
	static_assert(hamon::is_default_constructible<const_iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<const_iterator>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, T*>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, T const*>::value, "");
	static_assert(hamon::is_same<T const&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<T const*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
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

GTEST_TEST(ForwardListTest, iteratorTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test<short>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test<long>()));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace iterator_test

}	// namespace hamon_forward_list_test
