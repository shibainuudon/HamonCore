/**
 *	@file	unit_test_basic_const_iterator_types.cpp
 *
 *	@brief	Member types のテスト
 *
 *	using iterator_concept = see below;
 *	using iterator_category = see below;  // not always present
 *	using value_type = iter_value_t<Iterator>;
 *	using difference_type = iter_difference_t<Iterator>;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/concepts.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace types_test
{

// iterator_concept
static_assert(hamon::is_same<hamon::input_iterator_tag, typename hamon::basic_const_iterator<input_iterator_wrapper<int>>::iterator_concept>::value, "");
static_assert(hamon::is_same<hamon::forward_iterator_tag, typename hamon::basic_const_iterator<forward_iterator_wrapper<int>>::iterator_concept>::value, "");
static_assert(hamon::is_same<hamon::bidirectional_iterator_tag, typename hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>::iterator_concept>::value, "");
static_assert(hamon::is_same<hamon::random_access_iterator_tag, typename hamon::basic_const_iterator<random_access_iterator_wrapper<int>>::iterator_concept>::value, "");
static_assert(hamon::is_same<hamon::contiguous_iterator_tag, typename hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>::iterator_concept>::value, "");

// iterator_category
template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

static_assert(!has_iterator_category<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert( has_iterator_category<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( has_iterator_category<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( has_iterator_category<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( has_iterator_category<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

static_assert(hamon::is_same<hamon::forward_iterator_tag, typename hamon::basic_const_iterator<forward_iterator_wrapper<int>>::iterator_category>::value, "");
static_assert(hamon::is_same<hamon::bidirectional_iterator_tag, typename hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>::iterator_category>::value, "");
static_assert(hamon::is_same<hamon::random_access_iterator_tag, typename hamon::basic_const_iterator<random_access_iterator_wrapper<int>>::iterator_category>::value, "");
static_assert(hamon::is_same<hamon::random_access_iterator_tag, typename hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>::iterator_category>::value, "");

// value_type
static_assert(hamon::is_same<int, typename hamon::basic_const_iterator<input_iterator_wrapper<int>>::value_type>::value, "");
static_assert(hamon::is_same<int, typename hamon::basic_const_iterator<forward_iterator_wrapper<int>>::value_type>::value, "");
static_assert(hamon::is_same<int, typename hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>::value_type>::value, "");
static_assert(hamon::is_same<int, typename hamon::basic_const_iterator<random_access_iterator_wrapper<int>>::value_type>::value, "");
static_assert(hamon::is_same<int, typename hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>::value_type>::value, "");

// difference_type
static_assert(hamon::is_same<hamon::ptrdiff_t, typename hamon::basic_const_iterator<input_iterator_wrapper<int>>::difference_type>::value, "");
static_assert(hamon::is_same<hamon::ptrdiff_t, typename hamon::basic_const_iterator<forward_iterator_wrapper<int>>::difference_type>::value, "");
static_assert(hamon::is_same<hamon::ptrdiff_t, typename hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>::difference_type>::value, "");
static_assert(hamon::is_same<hamon::ptrdiff_t, typename hamon::basic_const_iterator<random_access_iterator_wrapper<int>>::difference_type>::value, "");
static_assert(hamon::is_same<hamon::ptrdiff_t, typename hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>::difference_type>::value, "");

}	// namespace types_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
