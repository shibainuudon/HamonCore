/**
 *	@file	unit_test_iterator_common_iterator_assign.cpp
 *
 *	@brief	代入演算子のテスト
 *
 *	template<class I2, class S2>
 *		requires convertible_to<const I2&, I> && convertible_to<const S2&, S> &&
 *			assignable_from<I&, const I2&> && assignable_from<S&, const S2&>
 *	constexpr common_iterator& operator=(const common_iterator<I2, S2>& x);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace assign_test {

template <typename T>
struct ConvertibleForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U, typename = hamon::enable_if_t<hamon::convertible_to_t<U*, T*>::value>>
	HAMON_CXX11_CONSTEXPR ConvertibleForwardIterator(ConvertibleForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ConvertibleForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T& operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ConvertibleForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ConvertibleForwardIterator& rhs) const { return !(*this == rhs); }
};

template <typename Iterator>
struct ConvertibleSentinel
{
	Iterator m_it;

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel() : m_it() {}

	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel(Iterator const& it) : m_it(it) {}

	template <typename U, typename = hamon::enable_if_t<hamon::convertible_to_t<U const&, Iterator>::value>>
	HAMON_CXX11_CONSTEXPR
	ConvertibleSentinel(ConvertibleSentinel<U> const& u) : m_it(u.m_it) {}
};

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(ConvertibleSentinel<T> const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return base(x.m_it) == base(y.m_it);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(ConvertibleSentinel<T> const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return !(x == y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(ConvertibleSentinel<T> const& x, U const& y) noexcept
{
	return base(x.m_it) == base(y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(ConvertibleSentinel<T> const& x, U const& y) noexcept
{
	return !(x == y);
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(T const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return y == x;
}

template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(T const& x, ConvertibleSentinel<U> const& y) noexcept
{
	return !(x == y);
}

}	// namespace assign_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test

namespace HAMON_COMMON_TYPE_NAMESPACE
{

template <typename T, typename U>
struct common_type<
	hamon_iterator_test::common_iterator_test::assign_test::ConvertibleForwardIterator<T>,
	hamon_iterator_test::common_iterator_test::assign_test::ConvertibleForwardIterator<U>
>
{
	using type = hamon_iterator_test::common_iterator_test::assign_test::ConvertibleForwardIterator<
		hamon::common_type_t<T, U>>;
};

template <typename T, typename U>
struct common_type<
	hamon_iterator_test::common_iterator_test::assign_test::ConvertibleSentinel<T>,
	hamon_iterator_test::common_iterator_test::assign_test::ConvertibleSentinel<U>
>
{
	using type = hamon_iterator_test::common_iterator_test::assign_test::ConvertibleSentinel<
		hamon::common_type_t<T, U>>;
};

}	// namespace HAMON_COMMON_TYPE_NAMESPACE

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace assign_test {

static_assert( hamon::convertible_to_t<ConvertibleForwardIterator<int> const&, ConvertibleForwardIterator<int const>>::value, "");
static_assert(!hamon::convertible_to_t<ConvertibleForwardIterator<int const> const&, ConvertibleForwardIterator<int>>::value, "");
static_assert( hamon::convertible_to_t<ConvertibleSentinel<ConvertibleForwardIterator<int>> const&, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>::value, "");
static_assert(!hamon::convertible_to_t<ConvertibleSentinel<ConvertibleForwardIterator<int const>> const&, ConvertibleSentinel<ConvertibleForwardIterator<int>>>::value, "");

static_assert( hamon::assignable_from_t<ConvertibleForwardIterator<int const>&, ConvertibleForwardIterator<int> const&>::value, "");
static_assert(!hamon::assignable_from_t<ConvertibleForwardIterator<int>&, ConvertibleForwardIterator<int const> const&>::value, "");
static_assert( hamon::assignable_from_t<ConvertibleSentinel<ConvertibleForwardIterator<int const>>&, ConvertibleSentinel<ConvertibleForwardIterator<int>> const&>::value, "");
static_assert(!hamon::assignable_from_t<ConvertibleSentinel<ConvertibleForwardIterator<int>>&, ConvertibleSentinel<ConvertibleForwardIterator<int const>> const&>::value, "");

static_assert( hamon::is_assignable<
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>&,
	hamon::common_iterator<ConvertibleForwardIterator<int      >, ConvertibleSentinel<ConvertibleForwardIterator<int const>>> const&>::value, "");
static_assert(!hamon::is_assignable<
	hamon::common_iterator<ConvertibleForwardIterator<int      >, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>&,
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int const>>> const&>::value, "");
static_assert( hamon::is_assignable<
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>&,
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int      >>> const&>::value, "");
static_assert(!hamon::is_assignable<
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int      >>>&,
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int const>>> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using I1 = ConvertibleForwardIterator<int const>;
	using I2 = ConvertibleForwardIterator<int>;
	using S1 = ConvertibleSentinel<I1>;
	using S2 = ConvertibleSentinel<I2>;
	static_assert(hamon::convertible_to_t<I2 const&, I1>::value, "");
	static_assert(hamon::convertible_to_t<S2 const&, S1>::value, "");
	static_assert(hamon::assignable_from_t<I1&, I2 const&>::value, "");
	static_assert(hamon::assignable_from_t<S1&, S2 const&>::value, "");
	int a[] = {1, 2, 3};
	I1 i1 {&a[0]};
	I2 i2 {&a[1]};
	S1 s1 {I1{&a[2]}};
	S2 s2 {I2{&a[3]}};
	{
		hamon::common_iterator<I1, S1> it1 {i1};
		hamon::common_iterator<I2, S2> it2 {i2};
		VERIFY(it1.operator->() == &a[0]);
		VERIFY(it2.operator->() == &a[1]);
		auto& t = (it1 = it2);
		VERIFY(it1.operator->() == &a[1]);
		VERIFY(it2.operator->() == &a[1]);
		VERIFY(&t == &it1);
	}
	{
		hamon::common_iterator<I1, S1> it1 {s1};
		hamon::common_iterator<I2, S2> it2 {s2};
		VERIFY(it1 == it2);
		auto& t = (it1 = it2);
		VERIFY(it1 == it2);
		VERIFY(&t == &it1);
	}
	{
		hamon::common_iterator<I1, S1> it1 {i1};
		hamon::common_iterator<I2, S2> it2 {s2};
		VERIFY(it1 != it2);
		auto& t = (it1 = it2);
		VERIFY(it1 == it2);
		VERIFY(&t == &it1);
	}
	{
		hamon::common_iterator<I1, S1> it1 {s1};
		hamon::common_iterator<I2, S2> it2 {i2};
		auto& t = (it1 = it2);
		VERIFY(it1.operator->() == &a[1]);
		VERIFY(it2.operator->() == &a[1]);
		VERIFY(&t == &it1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, AssignTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test00());
}

}	// namespace assign_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
