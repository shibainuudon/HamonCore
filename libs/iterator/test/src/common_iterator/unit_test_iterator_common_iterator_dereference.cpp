/**
 *	@file	unit_test_iterator_common_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr decltype(auto) operator*();
 *	constexpr decltype(auto) operator*() const
 *		requires dereferenceable<const I>;
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace dereference_test {

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	TestIterator& operator++();
	void          operator++(int);
	T&            operator*();
	bool operator==(const TestIterator& rhs);
	bool operator!=(const TestIterator& rhs);
};

template <typename T, typename Reference, typename ConstReference>
struct ValueInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	HAMON_CXX14_CONSTEXPR ValueInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void           operator++(int) { ++m_ptr; }
	HAMON_CXX14_CONSTEXPR Reference      operator*() { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR ConstReference operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueInputIterator& rhs) const { return !(*this == rhs); }
};

template <typename T, typename = void>
struct has_dereference
	: public hamon::false_type {};

template <typename T>
struct has_dereference<T, hamon::void_t<decltype(*hamon::declval<T>())>>
	: public hamon::true_type {};

static_assert(has_dereference<hamon::common_iterator<int*, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_dereference<hamon::common_iterator<int const*, hamon::unreachable_sentinel_t>>::value, "");
static_assert(has_dereference<hamon::common_iterator<int*, hamon::unreachable_sentinel_t> const>::value, "");
static_assert(has_dereference<hamon::common_iterator<int const*, hamon::unreachable_sentinel_t> const>::value, "");

static_assert( has_dereference<hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert( has_dereference<hamon::common_iterator<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t> const>::value, "");
static_assert( has_dereference<hamon::common_iterator<TestIterator<int>, hamon::unreachable_sentinel_t>>::value, "");
static_assert(!has_dereference<hamon::common_iterator<TestIterator<int>, hamon::unreachable_sentinel_t> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using CI = hamon::common_iterator<int*, hamon::unreachable_sentinel_t>;
	int n = 42;
	{
		CI it{&n};
		static_assert(hamon::is_same<decltype(*it), int&>::value, "");
		VERIFY(*it == 42);
	}
	{
		CI const it{&n};
		static_assert(hamon::is_same<decltype(*it), int&>::value, "");
		VERIFY(*it == 42);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using CI = hamon::common_iterator<int const*, hamon::unreachable_sentinel_t>;
	int n = 43;
	{
		CI it{&n};
		static_assert(hamon::is_same<decltype(*it), int const&>::value, "");
		VERIFY(*it == 43);
	}
	{
		CI const it{&n};
		static_assert(hamon::is_same<decltype(*it), int const&>::value, "");
		VERIFY(*it == 43);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using I = ValueInputIterator<int, int, int&>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int n = 44;
	I i{&n};
	{
		CI it{i};
		static_assert(hamon::is_same<decltype(*it), int>::value, "");
		VERIFY(*it == 44);
	}
	{
		CI const it{i};
		static_assert(hamon::is_same<decltype(*it), int&>::value, "");
		VERIFY(*it == 44);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	using I = ValueInputIterator<int, int const&, int>;
	using CI = hamon::common_iterator<I, hamon::unreachable_sentinel_t>;
	int n = 44;
	I i{&n};
	{
		CI it{i};
		static_assert(hamon::is_same<decltype(*it), int const&>::value, "");
		VERIFY(*it == 44);
	}
	{
		CI const it{i};
		static_assert(hamon::is_same<decltype(*it), int>::value, "");
		VERIFY(*it == 44);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, DereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace dereference_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
