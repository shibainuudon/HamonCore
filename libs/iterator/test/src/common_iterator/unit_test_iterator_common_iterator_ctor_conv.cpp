/**
 *	@file	unit_test_iterator_common_iterator_ctor_conv.cpp
 *
 *	@brief	コンバートコンストラクタのテスト
 *
 *	template<class I2, class S2>
 *		requires convertible_to<const I2&, I> && convertible_to<const S2&, S>
 *	constexpr common_iterator(const common_iterator<I2, S2>& x);
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace ctor_conv_test {

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

static_assert( hamon::convertible_to_t<ConvertibleForwardIterator<int> const&, ConvertibleForwardIterator<int const>>::value, "");
static_assert(!hamon::convertible_to_t<ConvertibleForwardIterator<int const> const&, ConvertibleForwardIterator<int>>::value, "");
static_assert( hamon::convertible_to_t<ConvertibleSentinel<ConvertibleForwardIterator<int>> const&, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>::value, "");
static_assert(!hamon::convertible_to_t<ConvertibleSentinel<ConvertibleForwardIterator<int const>> const&, ConvertibleSentinel<ConvertibleForwardIterator<int>>>::value, "");

static_assert( hamon::is_constructible<
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>,
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>>::value, "");
static_assert( hamon::is_constructible<
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>,
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>>::value, "");
static_assert(!hamon::is_constructible<
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>,
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int const>>>>::value, "");
static_assert( hamon::is_constructible<
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>,
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>>::value, "");
static_assert(!hamon::is_constructible<
	hamon::common_iterator<ConvertibleForwardIterator<int>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>,
	hamon::common_iterator<ConvertibleForwardIterator<int const>, ConvertibleSentinel<ConvertibleForwardIterator<int>>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	int n = 42;
	hamon::common_iterator<int*, hamon::unreachable_sentinel_t> it1{&n};
	hamon::common_iterator<int const*, hamon::unreachable_sentinel_t> it2{it1};
	VERIFY(it2.operator->() == &n);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using I1 = ConvertibleForwardIterator<int>;
	using S1 = ConvertibleSentinel<I1>;
	using CI1 = hamon::common_iterator<I1, S1>;

	using I2 = ConvertibleForwardIterator<int const>;
	using S2 = ConvertibleSentinel<I2>;
	using CI2 = hamon::common_iterator<I2, S2>;
	
	static_assert(hamon::convertible_to_t<I1 const&, I2>::value, "");
	static_assert(hamon::convertible_to_t<S1 const&, S2>::value, "");

	int n = 42;
	{
		CI1 it1{I1{&n}};
		CI2 it2{it1};
		VERIFY(it2.operator->() == &n);
	}
	{
		CI1 it1{S1{I1{&n}}};
		CI2 it2{it1};
		VERIFY(it1 == it2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, CtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_conv_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
