/**
 *	@file	unit_test_iterator_common_iterator_iterator_traits.cpp
 *
 *	@brief	iterator_traits のテスト
 *
 *	template<input_iterator I, class S>
 *	struct iterator_traits<common_iterator<I, S>> {
 *		using iterator_concept = see below;
 *		using iterator_category = see below;  // not always present
 *		using value_type = iter_value_t<I>;
 *		using difference_type = iter_difference_t<I>;
 *		using pointer = see below;
 *		using reference = iter_reference_t<I>;
 *	};
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/detail/signed_integer_class.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace iterator_traits_test {

struct SignedIntegerLike {};

}	// namespace iterator_traits_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test

template <>
struct hamon::detail::signed_integer_class<
	hamon_iterator_test::common_iterator_test::iterator_traits_test::SignedIntegerLike>
	: public hamon::true_type {};

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace iterator_traits_test {

template <typename T>
struct TestIterator1
{
	//using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	TestIterator1& operator++();
	TestIterator1  operator++(int);
	T&             operator*() const;
	bool operator==(const TestIterator1& rhs) const;
	bool operator!=(const TestIterator1& rhs) const;
};

}	// namespace iterator_traits_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test

template <typename T>
struct HAMON_ITERATOR_TRAITS_NAMESPACE::iterator_traits<
	hamon_iterator_test::common_iterator_test::iterator_traits_test::TestIterator1<T>>
{
	using iterator_concept = hamon::forward_iterator_tag;
	using value_type       = T;
	using difference_type  = hamon::ptrdiff_t;
	using pointer          = T*;
	using reference        = T&;
};

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace iterator_traits_test {

static_assert( hamon::input_iterator_t<TestIterator1<int>>::value, "");

#if !defined(HAMON_USE_STD_COMMON_ITERATOR)

template <typename T>
struct TestIterator2
{
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = SignedIntegerLike;
	using pointer           = T*;
	using reference         = T&;
	TestIterator2& operator++();
	void           operator++(int);
	T&             operator*() const;
	bool operator==(const TestIterator2& rhs) const;
	bool operator!=(const TestIterator2& rhs) const;
};

static_assert( hamon::input_iterator_t<TestIterator2<int>>::value, "");
static_assert(!hamon::integral_t<hamon::iter_difference_t<TestIterator2<int>>>::value, "");

#endif

struct Dummy
{
	Dummy(Dummy&)=delete;
};

template <typename T>
struct TestIterator3
{
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = Dummy;
	using difference_type   = hamon::ptrdiff_t;
	TestIterator3& operator++();
	void           operator++(int);
	Dummy          operator*() const;
	bool operator==(const TestIterator3& rhs) const;
	bool operator!=(const TestIterator3& rhs) const;
};

static_assert( hamon::input_iterator_t<TestIterator3<int>>::value, "");

template <typename T>
struct TestIterator4
{
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = Dummy;
	using difference_type   = hamon::ptrdiff_t;
	TestIterator4& operator++();
	void           operator++(int);
	T&             operator*() const;
	bool operator==(const TestIterator4& rhs) const;
	bool operator!=(const TestIterator4& rhs) const;
};

static_assert( hamon::input_or_output_iterator_t<TestIterator4<int>>::value, "");
static_assert(!hamon::input_iterator_t<TestIterator4<int>>::value, "");

template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_iterator_concept
	: public hamon::false_type {};

template <typename T>
struct has_iterator_concept<T, hamon::void_t<typename T::iterator_concept>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_value_type
	: public hamon::false_type {};

template <typename T>
struct has_value_type<T, hamon::void_t<typename T::value_type>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_difference_type
	: public hamon::false_type {};

template <typename T>
struct has_difference_type<T, hamon::void_t<typename T::difference_type>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pointer
	: public hamon::false_type {};

template <typename T>
struct has_pointer<T, hamon::void_t<typename T::pointer>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_reference
	: public hamon::false_type {};

template <typename T>
struct has_reference<T, hamon::void_t<typename T::reference>>
	: public hamon::true_type {};

GTEST_TEST(CommonIteratorTest, IteratorTraitsTest)
{
	{
		using CI = hamon::common_iterator<int*, int const*>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert( has_iterator_concept<Traits>::value, "");
		static_assert( has_iterator_category<Traits>::value, "");
		static_assert( has_value_type<Traits>::value, "");
		static_assert( has_difference_type<Traits>::value, "");
		static_assert( has_pointer<Traits>::value, "");
		static_assert( has_reference<Traits>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_concept,  hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::value_type,        int>::value, "");
		static_assert(hamon::is_same<typename Traits::difference_type,   hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<typename Traits::pointer,           int*>::value, "");
		static_assert(hamon::is_same<typename Traits::reference,         int&>::value, "");
	}
	{
		using CI = hamon::common_iterator<input_iterator_wrapper<char>, test_sentinel<input_iterator_wrapper<char>>>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert( has_iterator_concept<Traits>::value, "");
		static_assert( has_iterator_category<Traits>::value, "");
		static_assert( has_value_type<Traits>::value, "");
		static_assert( has_difference_type<Traits>::value, "");
		static_assert( has_pointer<Traits>::value, "");
		static_assert( has_reference<Traits>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_concept,  hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::value_type,        char>::value, "");
		static_assert(hamon::is_same<typename Traits::difference_type,   hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<typename Traits::pointer,           char*>::value, "");
		static_assert(hamon::is_same<typename Traits::reference,         char&>::value, "");
	}
	{
		using CI = hamon::common_iterator<forward_iterator_wrapper<char const>, test_sentinel<forward_iterator_wrapper<char const>>>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert( has_iterator_concept<Traits>::value, "");
		static_assert( has_iterator_category<Traits>::value, "");
		static_assert( has_value_type<Traits>::value, "");
		static_assert( has_difference_type<Traits>::value, "");
		static_assert( has_pointer<Traits>::value, "");
		static_assert( has_reference<Traits>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_concept,  hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::value_type,        char>::value, "");
		static_assert(hamon::is_same<typename Traits::difference_type,   hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<typename Traits::pointer,           char const*>::value, "");
		static_assert(hamon::is_same<typename Traits::reference,         char const&>::value, "");
	}
	{
		using CI = hamon::common_iterator<TestIterator1<int>, hamon::unreachable_sentinel_t>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert( has_iterator_concept<Traits>::value, "");
		static_assert( has_iterator_category<Traits>::value, "");
		static_assert( has_value_type<Traits>::value, "");
		static_assert( has_difference_type<Traits>::value, "");
		static_assert( has_pointer<Traits>::value, "");
		static_assert( has_reference<Traits>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_concept,  hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::value_type,        int>::value, "");
		static_assert(hamon::is_same<typename Traits::difference_type,   hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<typename Traits::pointer,           int*>::value, "");
		static_assert(hamon::is_same<typename Traits::reference,         int&>::value, "");
	}
#if !defined(HAMON_USE_STD_COMMON_ITERATOR)
	{
		using CI = hamon::common_iterator<TestIterator2<int>, hamon::unreachable_sentinel_t>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert( has_iterator_concept<Traits>::value, "");
		static_assert(!has_iterator_category<Traits>::value, "");	// MSVC-STLでは正しく実装されていない(常にiterator_categoryを持つ)
		static_assert( has_value_type<Traits>::value, "");
		static_assert( has_difference_type<Traits>::value, "");
		static_assert( has_pointer<Traits>::value, "");
		static_assert( has_reference<Traits>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_concept,  hamon::input_iterator_tag>::value, "");
//		static_assert(hamon::is_same<typename Traits::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::value_type,        int>::value, "");
		static_assert(hamon::is_same<typename Traits::difference_type,   SignedIntegerLike>::value, "");
		static_assert(hamon::is_same<typename Traits::pointer,           int*>::value, "");
		static_assert(hamon::is_same<typename Traits::reference,         int&>::value, "");
	}
#endif
	{
		using CI = hamon::common_iterator<TestIterator3<int>, hamon::unreachable_sentinel_t>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert( has_iterator_concept<Traits>::value, "");
		static_assert( has_iterator_category<Traits>::value, "");
		static_assert( has_value_type<Traits>::value, "");
		static_assert( has_difference_type<Traits>::value, "");
		static_assert( has_pointer<Traits>::value, "");
		static_assert( has_reference<Traits>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_concept,  hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::iterator_category, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename Traits::value_type,        Dummy>::value, "");
		static_assert(hamon::is_same<typename Traits::difference_type,   hamon::ptrdiff_t>::value, "");
		static_assert(hamon::is_same<typename Traits::pointer,           void>::value, "");
		static_assert(hamon::is_same<typename Traits::reference,         Dummy>::value, "");
	}
	{
		using CI = hamon::common_iterator<TestIterator4<int>, hamon::unreachable_sentinel_t>;
		using Traits = hamon::iterator_traits<CI>;
		static_assert(!has_iterator_concept<Traits>::value, "");
		static_assert(!has_iterator_category<Traits>::value, "");
		static_assert(!has_value_type<Traits>::value, "");
		static_assert(!has_difference_type<Traits>::value, "");
		static_assert(!has_pointer<Traits>::value, "");
		static_assert(!has_reference<Traits>::value, "");
	}
}

}	// namespace iterator_traits_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
