/**
 *	@file	unit_test_iterator_common_iterator_arrow.cpp
 *
 *	@brief	operator-> のテスト
 *
 *	constexpr auto operator->() const
 *		requires see below;
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace arrow_test {

template <typename T>
struct ValueInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = Reference;
	HAMON_CXX14_CONSTEXPR ValueInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void          operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T             operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueInputIterator& rhs) const { return !(*this == rhs); }
};

template <typename T, bool HasArrow, typename ValueType = T, typename Reference = T&, typename ConstReference = T&>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = ValueType;
	using difference_type   = hamon::ptrdiff_t;
	TestIterator&  operator++();
	void           operator++(int);
	Reference      operator*();
	ConstReference operator*() const;
	template <bool B2 = HasArrow, typename = hamon::enable_if_t<B2>>
	T* operator->() const;
	bool operator==(const TestIterator& rhs) const;
	bool operator!=(const TestIterator& rhs) const;
};

template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

static_assert(has_arrow<hamon::common_iterator<int*, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_arrow<hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_arrow<hamon::common_iterator<forward_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_arrow<hamon::common_iterator<bidirectional_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_arrow<hamon::common_iterator<random_access_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_arrow<hamon::common_iterator<contiguous_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");

struct Dummy
{
	Dummy(int){}
	Dummy(Dummy&)=delete;
};

using TestIter1 = TestIterator<int, true, int, int&>;
static_assert( hamon::indirectly_readable_t<TestIter1 const>::value, "");
static_assert( has_arrow<TestIter1 const&>::value, "");
static_assert( hamon::is_reference<hamon::iter_reference_t<TestIter1>>::value, "");
static_assert( hamon::constructible_from_t<hamon::iter_value_t<TestIter1>, hamon::iter_reference_t<TestIter1>>::value, "");

using TestIter2 = TestIterator<int, true, Dummy, int&, int const&>;
static_assert(!hamon::indirectly_readable_t<TestIter2 const>::value, "");
static_assert( has_arrow<TestIter2 const&>::value, "");
static_assert( hamon::is_reference<hamon::iter_reference_t<TestIter2>>::value, "");
static_assert( hamon::constructible_from_t<hamon::iter_value_t<TestIter2>, hamon::iter_reference_t<TestIter2>>::value, "");

using TestIter3 = TestIterator<int, true, Dummy, Dummy, Dummy>;
static_assert( hamon::indirectly_readable_t<TestIter3 const>::value, "");
static_assert( has_arrow<TestIter3 const&>::value, "");
static_assert(!hamon::is_reference<hamon::iter_reference_t<TestIter3>>::value, "");
static_assert(!hamon::constructible_from_t<hamon::iter_value_t<TestIter3>, hamon::iter_reference_t<TestIter3>>::value, "");

using TestIter4 = TestIterator<int, false, Dummy, Dummy&, Dummy&>;
static_assert( hamon::indirectly_readable_t<TestIter4 const>::value, "");
static_assert(!has_arrow<TestIter4 const&>::value, "");
static_assert( hamon::is_reference<hamon::iter_reference_t<TestIter4>>::value, "");
static_assert(!hamon::constructible_from_t<hamon::iter_value_t<TestIter4>, hamon::iter_reference_t<TestIter4>>::value, "");

using TestIter5 = TestIterator<int, false, int, int, int>;
static_assert( hamon::indirectly_readable_t<TestIter5 const>::value, "");
static_assert(!has_arrow<TestIter5 const&>::value, "");
static_assert(!hamon::is_reference<hamon::iter_reference_t<TestIter5>>::value, "");
static_assert( hamon::constructible_from_t<hamon::iter_value_t<TestIter5>, hamon::iter_reference_t<TestIter5>>::value, "");

using TestIter6 = TestIterator<int, false, Dummy, Dummy, Dummy>;
static_assert( hamon::indirectly_readable_t<TestIter6 const>::value, "");
static_assert(!has_arrow<TestIter6 const&>::value, "");
static_assert(!hamon::is_reference<hamon::iter_reference_t<TestIter6>>::value, "");
static_assert(!hamon::constructible_from_t<hamon::iter_value_t<TestIter6>, hamon::iter_reference_t<TestIter6>>::value, "");

static_assert( has_arrow<hamon::common_iterator<TestIter1, hamon::unreachable_sentinel_t>>::value, "");
static_assert(!has_arrow<hamon::common_iterator<TestIter2, hamon::unreachable_sentinel_t>>::value, "");
static_assert( has_arrow<hamon::common_iterator<TestIter3, hamon::unreachable_sentinel_t>>::value, "");
static_assert( has_arrow<hamon::common_iterator<TestIter4, hamon::unreachable_sentinel_t>>::value, "");
static_assert( has_arrow<hamon::common_iterator<TestIter5, hamon::unreachable_sentinel_t>>::value, "");
static_assert(!has_arrow<hamon::common_iterator<TestIter6, hamon::unreachable_sentinel_t>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using CI = hamon::common_iterator<int*, hamon::unreachable_sentinel_t>;
	int n = 42;
	CI it{&n};
	
	static_assert( hamon::is_same<decltype(it.operator->()), int*>::value, "");
	
	VERIFY(it.operator->() == &n);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using I = contiguous_iterator_wrapper<int>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int n = 42;
	I i{&n};
	CI it{i};
	
	static_assert(!hamon::is_same<decltype(it.operator->()), int*>::value, "");
	static_assert( hamon::is_same<decltype(it.operator->()), I>::value, "");
	
	VERIFY(it.operator->() == i);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using I = random_access_iterator_wrapper<int>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int n = 42;
	I i{&n};
	CI it{i};

	static_assert( hamon::is_same<decltype(it.operator->()), int*>::value, "");
	static_assert(!hamon::is_same<decltype(it.operator->()), I>::value, "");
	
	VERIFY(it.operator->() == &n);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using I = ValueInputIterator<int>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int n = 42;
	I i{&n};
	CI it{i};

	static_assert(!hamon::is_same<decltype(it.operator->()), int*>::value, "");
	static_assert(!hamon::is_same<decltype(it.operator->()), I>::value, "");

	auto proxy = it.operator->();

	static_assert( hamon::is_same<decltype(proxy.operator->()), int const*>::value, "");
	static_assert(!hamon::is_same<decltype(proxy.operator->()), int*>::value, "");
	static_assert(!hamon::is_same<decltype(proxy.operator->()), I>::value, "");

	VERIFY(proxy.operator->() != &n);
	VERIFY(*proxy.operator->() == n);

	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, ArrowTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace arrow_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
