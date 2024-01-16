/**
 *	@file	unit_test_iterator_reverse_iterator_typedefs.cpp
 *
 *	@brief	reverse_iterator のテスト
 * 
 *	using iterator_type     = Iterator;
 *	using iterator_concept  = see below;
 *	using iterator_category = see below;
 *	using value_type        = iter_value_t<Iterator>;
 *	using difference_type   = iter_difference_t<Iterator>;
 *	using pointer           = typename iterator_traits<Iterator>::pointer;
 *	using reference         = iter_reference_t<Iterator>;
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace typedefs_test {

struct Iter1
{
	HAMON_CXX11_CONSTEXPR int operator*() const { return 0; }
};

struct Iter2
{
	HAMON_CXX11_CONSTEXPR int operator*() const { return 0; }
};

}	// namespace typedefs_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test

template <>
struct HAMON_ITERATOR_TRAITS_NAMESPACE::iterator_traits<
	hamon_iterator_test::reverse_iterator_test::typedefs_test::Iter1>
{
	using iterator_category = hamon::contiguous_iterator_tag;
	using difference_type = short;
	using value_type = char;
	using pointer = int;
};

template <>
struct HAMON_ITERATOR_TRAITS_NAMESPACE::iterator_traits<
	hamon_iterator_test::reverse_iterator_test::typedefs_test::Iter2>
{
	using iterator_category = hamon::input_iterator_tag;
	using difference_type = short;
	using value_type = char;
	using pointer = int;
};

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace typedefs_test {

GTEST_TEST(ReverseIteratorTest, TypedefsTest)
{
	{
		using I = int*;
		using RI = hamon::reverse_iterator<I>;
		static_assert(hamon::is_same<typename RI::iterator_type, I>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::value_type, hamon::iter_value_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::difference_type, hamon::iter_difference_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::pointer, typename hamon::iterator_traits<I>::pointer>::value, "");
		static_assert(hamon::is_same<typename RI::reference, hamon::iter_reference_t<I>>::value, "");
	}
	{
		using I = contiguous_iterator_wrapper<long>;
		using RI = hamon::reverse_iterator<I>;
		static_assert(hamon::is_same<typename RI::iterator_type, I>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::value_type, hamon::iter_value_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::difference_type, hamon::iter_difference_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::pointer, typename hamon::iterator_traits<I>::pointer>::value, "");
		static_assert(hamon::is_same<typename RI::reference, hamon::iter_reference_t<I>>::value, "");
	}
	{
		using I = random_access_iterator_wrapper<long>;
		using RI = hamon::reverse_iterator<I>;
		static_assert(hamon::is_same<typename RI::iterator_type, I>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_concept, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::value_type, hamon::iter_value_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::difference_type, hamon::iter_difference_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::pointer, typename hamon::iterator_traits<I>::pointer>::value, "");
		static_assert(hamon::is_same<typename RI::reference, hamon::iter_reference_t<I>>::value, "");
	}
	{
		using I = bidirectional_iterator_wrapper<double>;
		using RI = hamon::reverse_iterator<I>;
		static_assert(hamon::is_same<typename RI::iterator_type, I>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::value_type, hamon::iter_value_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::difference_type, hamon::iter_difference_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::pointer, typename hamon::iterator_traits<I>::pointer>::value, "");
		static_assert(hamon::is_same<typename RI::reference, hamon::iter_reference_t<I>>::value, "");
	}
	{
		using I = Iter1;
		using RI = hamon::reverse_iterator<I>;
		static_assert(hamon::is_same<typename RI::iterator_type, I>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_category, hamon::random_access_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::value_type, hamon::iter_value_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::difference_type, hamon::iter_difference_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::pointer, typename hamon::iterator_traits<I>::pointer>::value, "");
		static_assert(hamon::is_same<typename RI::reference, hamon::iter_reference_t<I>>::value, "");
	}
	{
		using I = Iter2;
		using RI = hamon::reverse_iterator<I>;
		static_assert(hamon::is_same<typename RI::iterator_type, I>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename RI::value_type, hamon::iter_value_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::difference_type, hamon::iter_difference_t<I>>::value, "");
		static_assert(hamon::is_same<typename RI::pointer, typename hamon::iterator_traits<I>::pointer>::value, "");
		static_assert(hamon::is_same<typename RI::reference, hamon::iter_reference_t<I>>::value, "");
	}
}

}	// namespace typedefs_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
