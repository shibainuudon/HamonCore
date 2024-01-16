/**
 *	@file	unit_test_iterator_reverse_iterator_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Iterator1, class Iterator2>
 *	constexpr bool operator==(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 *
 *	template<class Iterator1, class Iterator2>
 *	constexpr bool operator!=(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 *
 *	template<class Iterator1, class Iterator2>
 *	constexpr bool operator<(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 *
 *	template<class Iterator1, class Iterator2>
 *	constexpr bool operator>(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 *
 *	template<class Iterator1, class Iterator2>
 *	constexpr bool operator<=(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 *
 *	template<class Iterator1, class Iterator2>
 *	constexpr bool operator>=(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 *
 *	template<class Iterator1, three_way_comparable_with<Iterator1> Iterator2>
 *	constexpr compare_three_way_result_t<Iterator1, Iterator2>
 *	operator<=>(
 *		const reverse_iterator<Iterator1>& x,
 *		const reverse_iterator<Iterator2>& y);
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/is_gt.hpp>
#include <hamon/compare/is_lt.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace compare_test {

template <bool Convertible, bool NoExcept>
struct CompareResult
{
	HAMON_CXX11_CONSTEXPR operator bool() const noexcept(NoExcept);
};

template <bool NoExcept>
struct CompareResult<false, NoExcept>
{
};

template <bool Convertible, bool NoExcept>
struct TestIterator
{
	using T = int;
	T*	m_ptr;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX11_CONSTEXPR T& operator*() const noexcept { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR CompareResult<Convertible, NoExcept> operator==(const TestIterator& rhs) const noexcept;
	HAMON_CXX11_CONSTEXPR CompareResult<Convertible, NoExcept> operator!=(const TestIterator& rhs) const noexcept;
	HAMON_CXX11_CONSTEXPR CompareResult<Convertible, NoExcept> operator< (const TestIterator& rhs) const noexcept;
	HAMON_CXX11_CONSTEXPR CompareResult<Convertible, NoExcept> operator> (const TestIterator& rhs) const noexcept;
	HAMON_CXX11_CONSTEXPR CompareResult<Convertible, NoExcept> operator<=(const TestIterator& rhs) const noexcept;
	HAMON_CXX11_CONSTEXPR CompareResult<Convertible, NoExcept> operator>=(const TestIterator& rhs) const noexcept;
};

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

static_assert( has_eq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_eq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert( has_eq<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_eq<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_eq<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");

static_assert( has_neq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_neq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert( has_neq<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_neq<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_neq<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");

static_assert( has_lt<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_lt<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_lt<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert(!has_lt<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert(!has_lt<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert(!has_lt<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert( has_lt<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert( has_lt<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert( has_lt<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert( has_lt<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_lt<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_lt<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");

static_assert( has_lteq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_lteq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_lteq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert(!has_lteq<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert(!has_lteq<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert(!has_lteq<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert( has_lteq<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert( has_lteq<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert( has_lteq<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert( has_lteq<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_lteq<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_lteq<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");

static_assert( has_gt<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_gt<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_gt<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert(!has_gt<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert(!has_gt<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert(!has_gt<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert( has_gt<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert( has_gt<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert( has_gt<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert( has_gt<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_gt<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_gt<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");

static_assert( has_gteq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_gteq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_gteq<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert(!has_gteq<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert(!has_gteq<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert(!has_gteq<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert( has_gteq<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert( has_gteq<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert( has_gteq<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert( has_gteq<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_gteq<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_gteq<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
static_assert( has_compare_three_way<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int*>>::value,"");
static_assert( has_compare_three_way<hamon::reverse_iterator<int*>, hamon::reverse_iterator<int const*>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<int*>, hamon::reverse_iterator<long*>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<input_iterator_wrapper<int>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<forward_iterator_wrapper<int>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<TestIterator<true,  true>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<TestIterator<true,  false>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<TestIterator<false, true>>>::value,"");
static_assert(!has_compare_three_way<hamon::reverse_iterator<TestIterator<false, false>>>::value,"");
#endif

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() == hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() != hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() <  hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() >  hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() <= hamon::declval<hamon::reverse_iterator<int*>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() >= hamon::declval<hamon::reverse_iterator<int*>>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<int*>>() <=> hamon::declval<hamon::reverse_iterator<int*>>()), "");
#endif

static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>() == hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>() != hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>() <  hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>() >  hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>() <= hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>() >= hamon::declval<hamon::reverse_iterator<random_access_iterator_wrapper<int>>>()), "");

static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>() == hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>() != hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>() <  hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>() >  hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>() <= hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>()), "");
static_assert( noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>() >= hamon::declval<hamon::reverse_iterator<TestIterator<true, true>>>()), "");

static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>() == hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>() != hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>() <  hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>() >  hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>() <= hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>()), "");
static_assert(!noexcept(hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>() >= hamon::declval<hamon::reverse_iterator<TestIterator<true, false>>>()), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	char const* s = "123456789";
	hamon::reverse_iterator<char const*> it1(s+1);
	hamon::reverse_iterator<char const*> it2(s+2);
	hamon::reverse_iterator<char const*> it3(s+3);
	VERIFY((it2 == it1) == false);
	VERIFY((it2 == it2) == true);
	VERIFY((it2 == it3) == false);
	VERIFY((it2 != it1) == true);
	VERIFY((it2 != it2) == false);
	VERIFY((it2 != it3) == true);
	VERIFY((it2 <  it1) == true);
	VERIFY((it2 <  it2) == false);
	VERIFY((it2 <  it3) == false);
	VERIFY((it2 >  it1) == false);
	VERIFY((it2 >  it2) == false);
	VERIFY((it2 >  it3) == true);
	VERIFY((it2 <= it1) == true);
	VERIFY((it2 <= it2) == true);
	VERIFY((it2 <= it3) == false);
	VERIFY((it2 >= it1) == false);
	VERIFY((it2 >= it2) == true);
	VERIFY((it2 >= it3) == true);

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_lt(it2 <=> it1));
	VERIFY(hamon::is_eq(it2 <=> it2));
	VERIFY(hamon::is_gt(it2 <=> it3));
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(ReverseIteratorTest, CompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace compare_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
