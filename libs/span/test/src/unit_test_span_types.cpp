/**
 *	@file	unit_test_span_types.cpp
 *
 *	@brief
 */

#include <hamon/span.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <cstddef>
#include <iterator>
#include <string>
#include <gtest/gtest.h>

#define ASSERT_SAME_TYPE(...) \
    static_assert((hamon::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

namespace hamon_span_test
{

namespace types_test
{

template <typename S, typename Iter>
void testIterator()
{
	typedef hamon::iterator_traits<Iter> ItT;

	ASSERT_SAME_TYPE(typename ItT::iterator_category, std::random_access_iterator_tag);
	ASSERT_SAME_TYPE(typename ItT::value_type,        typename S::value_type);
	ASSERT_SAME_TYPE(typename ItT::reference,         typename S::reference);
	ASSERT_SAME_TYPE(typename ItT::pointer,           typename S::pointer);
	ASSERT_SAME_TYPE(typename ItT::difference_type,   typename S::difference_type);
}

template <typename S, typename ElementType, std::size_t Size>
void testSpan()
{
	ASSERT_SAME_TYPE(typename S::element_type,    ElementType);
	ASSERT_SAME_TYPE(typename S::value_type,      hamon::remove_cv_t<ElementType>);
	ASSERT_SAME_TYPE(typename S::size_type,       std::size_t);
	ASSERT_SAME_TYPE(typename S::difference_type, std::ptrdiff_t);
	ASSERT_SAME_TYPE(typename S::pointer,         ElementType*);
	ASSERT_SAME_TYPE(typename S::const_pointer,   const ElementType*);
	ASSERT_SAME_TYPE(typename S::reference,       ElementType&);
	ASSERT_SAME_TYPE(typename S::const_reference, const ElementType&);

	static_assert(S::extent == Size, ""); // check that it exists

	testIterator<S, typename S::iterator>();
	//testIterator<S, typename S::reverse_iterator>();
}


template <typename T>
void test()
{
	testSpan<hamon::span<               T>,                T, hamon::dynamic_extent>();
	testSpan<hamon::span<const          T>, const          T, hamon::dynamic_extent>();
	testSpan<hamon::span<      volatile T>,       volatile T, hamon::dynamic_extent>();
	testSpan<hamon::span<const volatile T>, const volatile T, hamon::dynamic_extent>();

	testSpan<hamon::span<               T, 5>,                T, 5>();
	testSpan<hamon::span<const          T, 5>, const          T, 5>();
	testSpan<hamon::span<      volatile T, 5>,       volatile T, 5>();
	testSpan<hamon::span<const volatile T, 5>, const volatile T, 5>();
}

struct A {};

GTEST_TEST(SpanTest, TypesTest)
{
	test<int>();
	test<long>();
	test<double>();
	test<std::string>();
	test<A>();
}

}	// namespace types_test

}	// namespace hamon_span_test

#undef ASSERT_SAME_TYPE
