/**
 *	@file	unit_test_iterator_counted_iterator.cpp
 *
 *	@brief	counted_iterator のテスト
 */

#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/concepts.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/iterator/detail/dereferenceable.hpp>
#include <hamon/compare.hpp>
#include <hamon/concepts.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace counted_iterator_test
{

template <typename T, typename = void>
struct has_value_type
	: public hamon::false_type {};

template <typename T>
struct has_value_type<T, hamon::void_t<typename T::value_type>>
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
struct has_dereference
	: public hamon::false_type {};

template <typename T>
struct has_dereference<T, hamon::void_t<decltype(hamon::declval<T>().operator*())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_arrow
	: public hamon::false_type {};

template <typename T>
struct has_arrow<T, hamon::void_t<decltype(hamon::declval<T>().operator->())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_increment
	: public hamon::false_type {};

template <typename T>
struct has_post_increment<T, hamon::void_t<decltype(hamon::declval<T>()++)>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_pre_decrement
	: public hamon::false_type {};

template <typename T>
struct has_pre_decrement<T, hamon::void_t<decltype(--hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_post_decrement
	: public hamon::false_type {};

template <typename T>
struct has_post_decrement<T, hamon::void_t<decltype(hamon::declval<T>()--)>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_plus
	: public hamon::false_type {};

template <typename T, typename U>
struct has_plus<T, U, hamon::void_t<decltype(hamon::declval<T>() + hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_plus_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_plus_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() += hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_minus
	: public hamon::false_type {};

template <typename T, typename U>
struct has_minus<T, U, hamon::void_t<decltype(hamon::declval<T>() - hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_minus_equal
	: public hamon::false_type {};

template <typename T, typename U>
struct has_minus_equal<T, U, hamon::void_t<decltype(hamon::declval<T>() -= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_bracket
	: public hamon::false_type {};

template <typename T, typename U>
struct has_bracket<T, U, hamon::void_t<decltype(hamon::declval<T>()[hamon::declval<U>()])>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_eq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_eq<T, U, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_neq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_neq<T, U, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_lt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lt<T, U, hamon::void_t<decltype(hamon::declval<T>() < hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_lteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_lteq<T, U, hamon::void_t<decltype(hamon::declval<T>() <= hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_gt
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gt<T, U, hamon::void_t<decltype(hamon::declval<T>() > hamon::declval<U>())>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_gteq
	: public hamon::false_type {};

template <typename T, typename U>
struct has_gteq<T, U, hamon::void_t<decltype(hamon::declval<T>() >= hamon::declval<U>())>>
	: public hamon::true_type {};

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U, typename = void>
struct has_compare_three_way
	: public hamon::false_type {};

template <typename T, typename U>
struct has_compare_three_way<T, U, hamon::void_t<decltype(hamon::declval<T>() <=> hamon::declval<U>())>>
	: public hamon::true_type {};
#endif

template <typename T, typename = void>
struct has_iter_rvalue_reference_t
	: public hamon::false_type {};

template <typename T>
struct has_iter_rvalue_reference_t<T, hamon::void_t<hamon::iter_rvalue_reference_t<T>>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_iter_move
	: public hamon::false_type {};

template <typename T>
struct has_iter_move<T, hamon::void_t<decltype(hamon::ranges::iter_move(hamon::declval<T>()))>>
	: public hamon::true_type {};

template <typename T, typename U, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T, typename U>
struct has_iter_swap<T, U, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<U>()))>>
	: public hamon::true_type {};

template <typename I>
HAMON_CXX14_CONSTEXPR bool ConceptsTest()
{
	using CI = hamon::counted_iterator<I>;

	// using iterator_type = I;
	static_assert(hamon::same_as_t<typename CI::iterator_type, I>::value, "");
	
	// using value_type = iter_value_t<I>;
	static_assert(has_value_type<CI>::value == hamon::indirectly_readable_t<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_value_type<CI>::value)
	{
		static_assert(hamon::same_as_t<typename CI::value_type, hamon::iter_value_t<I>>::value, "");
	}
#endif

	// using difference_type = iter_difference_t<I>;
	static_assert(hamon::same_as_t<typename CI::difference_type, hamon::iter_difference_t<I>>::value, "");
	
	// using iterator_concept = typename I::iterator_concept;
	static_assert(has_iterator_concept<CI>::value == has_iterator_concept<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_iterator_concept<CI>::value)
	{
		static_assert(hamon::same_as_t<typename CI::iterator_concept, typename I::iterator_concept>::value, "");
	}
#endif

	// using iterator_category = typename I::iterator_category;
	static_assert(has_iterator_category<CI>::value == has_iterator_category<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_iterator_category<CI>::value)
	{
		static_assert(hamon::same_as_t<typename CI::iterator_category, typename I::iterator_category>::value, "");
	}
#endif

	// counted_iterator()
	static_assert( hamon::default_initializable_t<CI>::value == hamon::default_initializable_t<I>::value, "");
	
	// counted_iterator(I x, iter_difference_t<I> n);
	static_assert( hamon::constructible_from_t<CI, I, hamon::iter_difference_t<I>>::value, "");
	static_assert(!hamon::constructible_from_t<CI, I>::value, "");

	// const I& base() const & noexcept;
	// I base() &&;
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI &      >().base()), I const&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI &&     >().base()), I       >::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const& >().base()), I const&>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const&&>().base()), I const&>::value, "");

	// iter_difference_t<I> count() const noexcept;
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI      >().count()), hamon::iter_difference_t<I>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>().count()), hamon::iter_difference_t<I>>::value, "");

	// decltype(auto) operator*();
	static_assert(has_dereference<CI>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI>().operator*()), decltype(*hamon::declval<I>())>::value, "");
	// decltype(auto) operator*() const;
	static_assert(has_dereference<CI const>::value == hamon::detail::dereferenceable_t<I const>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_dereference<CI const>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>().operator*()), decltype(*hamon::declval<I const>())>::value, "");
	}
#endif

	// auto operator->() const noexcept;
	static_assert(has_arrow<CI const>::value == hamon::contiguous_iterator_t<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_arrow<CI const>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>().operator->()), decltype(hamon::to_address(hamon::declval<I>()))>::value, "");
	}
#endif

	// counted_iterator& operator++();
	static_assert( has_pre_increment<CI>::value, "");
	static_assert(!has_pre_increment<CI const>::value, "");
	static_assert(hamon::same_as_t<decltype(++hamon::declval<CI>()), CI&>::value, "");

	// counted_iterator operator++(int);
	// decltype(auto) operator++(int);
	static_assert( has_post_increment<CI>::value, "");
	static_assert(!has_post_increment<CI const>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::forward_iterator_t<I>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI>()++), CI>::value, "");
	}
	else
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI>()++), decltype(hamon::declval<I>()++)>::value, "");
	}
#endif

	// counted_iterator& operator--();
	static_assert( has_pre_decrement<CI>::value == hamon::bidirectional_iterator_t<I>::value, "");
	static_assert(!has_pre_decrement<CI const>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_pre_decrement<CI>::value)
	{
		static_assert(hamon::same_as_t<decltype(--hamon::declval<CI>()), CI&>::value, "");
	}
#endif

	// counted_iterator operator--(int)
	static_assert( has_post_decrement<CI>::value == hamon::bidirectional_iterator_t<I>::value, "");
	static_assert(!has_post_decrement<CI const>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_post_decrement<CI>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI>()--), CI>::value, "");
	}
#endif

	// counted_iterator operator+(iter_difference_t<I> n) const;
	// counted_iterator operator+(iter_difference_t<I> n, const counted_iterator& x)
	// counted_iterator& operator+=(iter_difference_t<I> n);
	static_assert(has_plus<CI const, hamon::iter_difference_t<I>>::value == hamon::random_access_iterator_t<I>::value, "");
	static_assert(has_plus<hamon::iter_difference_t<I>, CI const>::value == hamon::random_access_iterator_t<I>::value, "");
	static_assert(has_plus_equal<CI, hamon::iter_difference_t<I>>::value == hamon::random_access_iterator_t<I>::value, "");
	static_assert(has_plus_equal<CI const, hamon::iter_difference_t<I>>::value == false, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::random_access_iterator_t<I>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() + hamon::declval<hamon::iter_difference_t<I>>()), CI>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<hamon::iter_difference_t<I>>() + hamon::declval<CI const>()), CI>::value, "");
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI>() += hamon::declval<hamon::iter_difference_t<I>>()), CI&>::value, "");
	}
#endif

	// counted_iterator operator-(iter_difference_t<I> n) const;
	static_assert(has_minus<CI const, hamon::iter_difference_t<I>>::value == hamon::random_access_iterator_t<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::random_access_iterator_t<I>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() - hamon::declval<hamon::iter_difference_t<I>>()), CI>::value, "");
	}
#endif

	// iter_difference_t<I2> operator-(const counted_iterator& x, const counted_iterator<I2>& y);
	static_assert(has_minus<CI const, CI const>::value == true, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() - hamon::declval<CI const>()), hamon::iter_difference_t<I>>::value, "");

	// iter_difference_t<I> operator-(const counted_iterator& x, default_sentinel_t);
	// iter_difference_t<I> operator-(default_sentinel_t, const counted_iterator& y);
	static_assert(has_minus<CI const, hamon::default_sentinel_t>::value == true, "");
	static_assert(has_minus<hamon::default_sentinel_t, CI const>::value == true, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() - hamon::declval<hamon::default_sentinel_t>()), hamon::iter_difference_t<I>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<hamon::default_sentinel_t>() - hamon::declval<CI const>()), hamon::iter_difference_t<I>>::value, "");

	// counted_iterator& operator-=(iter_difference_t<I> n);
	static_assert(has_minus_equal<CI const, hamon::iter_difference_t<I>>::value == false, "");
	static_assert(has_minus_equal<CI, hamon::iter_difference_t<I>>::value == hamon::random_access_iterator_t<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::random_access_iterator_t<I>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::declval<CI>() -= hamon::declval<hamon::iter_difference_t<I>>()), CI&>::value, "");
	}
#endif

	// decltype(auto) operator[](iter_difference_t<I> n) const;
	static_assert(has_bracket<CI, hamon::iter_difference_t<I>>::value == hamon::random_access_iterator_t<I>::value, "");
	static_assert(has_bracket<CI const, hamon::iter_difference_t<I>>::value == hamon::random_access_iterator_t<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (hamon::random_access_iterator_t<I>::value)
	{
		static_assert(hamon::same_as_t<
			decltype(hamon::declval<CI>()[hamon::declval<hamon::iter_difference_t<I>>()]),
			decltype(hamon::declval<I>()[hamon::declval<hamon::iter_difference_t<I>>()])>::value, "");
		static_assert(hamon::same_as_t<
			decltype(hamon::declval<CI const>()[hamon::declval<hamon::iter_difference_t<I>>()]),
			decltype(hamon::declval<I const>()[hamon::declval<hamon::iter_difference_t<I>>()])>::value, "");
	}
#endif

	// bool operator==(const counted_iterator& x, const counted_iterator<I2>& y);
	// constexpr strong_ordering operator<=>(const counted_iterator& x, const counted_iterator<I2>& y);
	static_assert(has_eq<CI const, CI const>::value, "");
	static_assert(has_neq<CI const, CI const>::value, "");
	static_assert(has_lt<CI const, CI const>::value, "");
	static_assert(has_lteq<CI const, CI const>::value, "");
	static_assert(has_gt<CI const, CI const>::value, "");
	static_assert(has_gteq<CI const, CI const>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(has_compare_three_way<CI const, CI const>::value, "");
#endif
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() == hamon::declval<CI const>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() != hamon::declval<CI const>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() <  hamon::declval<CI const>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() <= hamon::declval<CI const>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() >  hamon::declval<CI const>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() >= hamon::declval<CI const>()), bool>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() <=> hamon::declval<CI const>()), std::strong_ordering>::value, "");
#endif

	// bool operator==(const counted_iterator& x, default_sentinel_t);
	static_assert(has_eq<CI const, hamon::default_sentinel_t>::value, "");
	static_assert(has_neq<CI const, hamon::default_sentinel_t>::value, "");
	static_assert(!has_lt<CI const, hamon::default_sentinel_t>::value, "");
	static_assert(!has_lteq<CI const, hamon::default_sentinel_t>::value, "");
	static_assert(!has_gt<CI const, hamon::default_sentinel_t>::value, "");
	static_assert(!has_gteq<CI const, hamon::default_sentinel_t>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<CI const, hamon::default_sentinel_t>::value, "");
#endif
	static_assert(has_eq<hamon::default_sentinel_t, CI const>::value, "");
	static_assert(has_neq<hamon::default_sentinel_t, CI const>::value, "");
	static_assert(!has_lt<hamon::default_sentinel_t, CI const>::value, "");
	static_assert(!has_lteq<hamon::default_sentinel_t, CI const>::value, "");
	static_assert(!has_gt<hamon::default_sentinel_t, CI const>::value, "");
	static_assert(!has_gteq<hamon::default_sentinel_t, CI const>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<hamon::default_sentinel_t, CI const>::value, "");
#endif
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() == hamon::declval<hamon::default_sentinel_t>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI const>() != hamon::declval<hamon::default_sentinel_t>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<hamon::default_sentinel_t>() == hamon::declval<CI const>()), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::declval<hamon::default_sentinel_t>() != hamon::declval<CI const>()), bool>::value, "");

	// iter_rvalue_reference_t<I> iter_move(const counted_iterator& i)
//	static_assert(has_iter_move<CI const>::value == hamon::input_iterator_t<I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_iter_move<CI const>::value)
	{
		static_assert(hamon::same_as_t<decltype(hamon::ranges::iter_move(hamon::declval<CI const>())), hamon::iter_rvalue_reference_t<I>>::value, "");
	}
#endif

	// void iter_swap(const counted_iterator& x, const counted_iterator<I2>& y);
	static_assert(has_iter_swap<CI const, CI const>::value == hamon::indirectly_swappable_t<I, I>::value, "");
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
	if constexpr (has_iter_swap<CI const, CI const>::value)
	{
		static_assert(hamon::same_as_t<decltype(iter_swap(hamon::declval<CI const>(), hamon::declval<CI const>())), void>::value, "");
	}
#endif

	return true;
}

GTEST_TEST(CountedIteratorTest, ConceptsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<int*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<int const*>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<input_or_output_iterator_wrapper<char>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<input_iterator_wrapper<float>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<output_iterator_wrapper<short>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<forward_iterator_wrapper<int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<bidirectional_iterator_wrapper<long>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<random_access_iterator_wrapper<unsigned int>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ConceptsTest<contiguous_iterator_wrapper<unsigned long long>>());

	// template<class I2>
	// requires convertible_to<const I2&, I>
	// constexpr counted_iterator(const counted_iterator<I2>& x);
	{
		using CI = hamon::counted_iterator<int*>;
		static_assert( hamon::constructible_from_t<CI, hamon::counted_iterator<int*>       const&>::value, "");
		static_assert(!hamon::constructible_from_t<CI, hamon::counted_iterator<int const*> const&>::value, "");
	}
	{
		using CI = hamon::counted_iterator<int const*>;
		static_assert( hamon::constructible_from_t<CI, hamon::counted_iterator<int*>       const&>::value, "");
		static_assert( hamon::constructible_from_t<CI, hamon::counted_iterator<int const*> const&>::value, "");
	}

	// template<class I2>
	// requires assignable_from<I&, const I2&>
	// constexpr counted_iterator& operator=(const counted_iterator<I2>& x);
	{
		using CI = hamon::counted_iterator<int*>;
		static_assert( hamon::assignable_from_t<CI&, hamon::counted_iterator<int*>       const&>::value, "");
		static_assert(!hamon::assignable_from_t<CI&, hamon::counted_iterator<int const*> const&>::value, "");
	}
	{
		using CI = hamon::counted_iterator<int const*>;
		static_assert( hamon::assignable_from_t<CI&, hamon::counted_iterator<int*>       const&>::value, "");
		static_assert( hamon::assignable_from_t<CI&, hamon::counted_iterator<int const*> const&>::value, "");
	}

	// template<common_with<I> I2>
	// friend constexpr iter_difference_t<I2> operator-(
	// const counted_iterator& x, const counted_iterator<I2>& y);
	static_assert( has_minus<hamon::counted_iterator<int*>, hamon::counted_iterator<int*>>::value == true, "");
	static_assert( has_minus<hamon::counted_iterator<int*>, hamon::counted_iterator<int const*>>::value == true, "");
	static_assert(!has_minus<hamon::counted_iterator<int*>, hamon::counted_iterator<long*>>::value == true, "");
	static_assert( has_minus<hamon::counted_iterator<long*>, hamon::counted_iterator<long*>>::value == true, "");

	// template<common_with<I> I2>
	// friend constexpr bool operator==(
	// const counted_iterator& x, const counted_iterator<I2>& y);
	static_assert( has_eq<hamon::counted_iterator<int*>, hamon::counted_iterator<int*>>::value, "");
	static_assert( has_eq<hamon::counted_iterator<int*>, hamon::counted_iterator<int const*>>::value, "");
	static_assert(!has_eq<hamon::counted_iterator<int*>, hamon::counted_iterator<long*>>::value, "");
	static_assert( has_eq<hamon::counted_iterator<long*>, hamon::counted_iterator<long*>>::value, "");

	// template<indirectly_swappable<I> I2>
	// friend constexpr void iter_swap(const counted_iterator& x, const counted_iterator<I2>& y)
	// noexcept(noexcept(ranges::iter_swap(x.current, y.current)));
	static_assert( has_iter_swap<hamon::counted_iterator<int*>, hamon::counted_iterator<int*>>::value == true, "");
	static_assert(!has_iter_swap<hamon::counted_iterator<int*>, hamon::counted_iterator<int const*>>::value == true, "");
	static_assert( has_iter_swap<hamon::counted_iterator<int*>, hamon::counted_iterator<long*>>::value == true, "");
	static_assert( has_iter_swap<hamon::counted_iterator<int*>, hamon::counted_iterator<random_access_iterator_wrapper<int>>>::value == true, "");
}

GTEST_TEST(CountedIteratorTest, IteratorTraitsTest)
{
	{
		using I = int*;
		using CI = hamon::counted_iterator<I>;
		using ITraits = hamon::iterator_traits<I>;
		using CITraits = hamon::iterator_traits<CI>;
		static_assert(hamon::same_as_t<CITraits::difference_type, ITraits::difference_type>::value, "");
		static_assert(hamon::same_as_t<CITraits::value_type, ITraits::value_type>::value, "");
		static_assert(hamon::same_as_t<CITraits::pointer, ITraits::pointer>::value, "");
		static_assert(hamon::same_as_t<CITraits::reference, ITraits::reference>::value, "");
		static_assert(hamon::same_as_t<CITraits::iterator_category, ITraits::iterator_category>::value, "");
	}
	{
		using I = random_access_iterator_wrapper<long>;
		using CI = hamon::counted_iterator<I>;
		using ITraits = hamon::iterator_traits<I>;
		using CITraits = hamon::iterator_traits<CI>;
		static_assert(hamon::same_as_t<CITraits::difference_type, ITraits::difference_type>::value, "");
		static_assert(hamon::same_as_t<CITraits::value_type, ITraits::value_type>::value, "");
		static_assert(hamon::same_as_t<CITraits::pointer, void>::value, "");
		static_assert(hamon::same_as_t<CITraits::reference, ITraits::reference>::value, "");
		static_assert(hamon::same_as_t<CITraits::iterator_category, ITraits::iterator_category>::value, "");
	}
	{
		using I = contiguous_iterator_wrapper<double>;
		using CI = hamon::counted_iterator<I>;
		using ITraits = hamon::iterator_traits<I>;
		using CITraits = hamon::iterator_traits<CI>;
		static_assert(hamon::same_as_t<CITraits::difference_type, ITraits::difference_type>::value, "");
		static_assert(hamon::same_as_t<CITraits::value_type, ITraits::value_type>::value, "");
		static_assert(hamon::same_as_t<CITraits::pointer, double*>::value, "");
		static_assert(hamon::same_as_t<CITraits::reference, ITraits::reference>::value, "");
		static_assert(hamon::same_as_t<CITraits::iterator_category, ITraits::iterator_category>::value, "");
	}
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	hamon::counted_iterator<int*> i{};
	VERIFY(i.count() == 0);
	VERIFY(i.base() == nullptr);
	
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	auto i = hamon::counted_iterator(a, 3);
#else
	auto i = hamon::counted_iterator<int*>(a, 3);
#endif
	VERIFY(i.count() == 3);
	VERIFY(i.base() == a);
	VERIFY(hamon::move(i).base() == a);
	VERIFY(i.operator->() == a);
	VERIFY(*i == 1);
	VERIFY(*hamon::as_const(i) == 1);
	VERIFY(i - hamon::default_sentinel == -3);
	VERIFY(hamon::default_sentinel - i == 3);
	VERIFY(i != hamon::default_sentinel);
	VERIFY(hamon::default_sentinel != i);
	*i = 42;
	auto& t1 = ++i;
	VERIFY(i.count() == 2);
	VERIFY(i.base() == a+1);
	VERIFY(hamon::move(i).base() == a+1);
	VERIFY(i.operator->() == a+1);
	VERIFY(*i == 2);
	VERIFY(&t1 == &i);
	VERIFY(i - hamon::default_sentinel == -2);
	VERIFY(hamon::default_sentinel - i == 2);
	VERIFY(i != hamon::default_sentinel);
	VERIFY(hamon::default_sentinel != i);
	auto t2 = i++;
	VERIFY(i.count() == 1);
	VERIFY(i.base() == a+2);
	VERIFY(hamon::move(i).base() == a+2);
	VERIFY(i.operator->() == a+2);
	VERIFY(*i == 3);
	VERIFY(t2 != i);
	VERIFY(*t2 == 2);
	VERIFY(i - hamon::default_sentinel == -1);
	VERIFY(hamon::default_sentinel - i == 1);
	VERIFY(i != hamon::default_sentinel);
	VERIFY(hamon::default_sentinel != i);
	auto& t3 = (i += 1);
	VERIFY(i.count() == 0);
	VERIFY(i.base() == a+3);
	VERIFY(hamon::move(i).base() == a+3);
	VERIFY(i.operator->() == a+3);
	VERIFY(&t3 == &i);
	VERIFY(i - hamon::default_sentinel == 0);
	VERIFY(hamon::default_sentinel - i == 0);
	VERIFY(i == hamon::default_sentinel);
	VERIFY(hamon::default_sentinel == i);
	auto& t4 = --i;
	VERIFY(i.count() == 1);
	VERIFY(i.base() == a+2);
	VERIFY(hamon::move(i).base() == a+2);
	VERIFY(i.operator->() == a+2);
	VERIFY(*i == 3);
	VERIFY(&t4 == &i);
	auto t5 = i--;
	VERIFY(i.count() == 2);
	VERIFY(i.base() == a+1);
	VERIFY(hamon::move(i).base() == a+1);
	VERIFY(i.operator->() == a+1);
	VERIFY(*i == 2);
	VERIFY(t5 != i);
	VERIFY(*t5 == 3);
	auto& t6 = (i -= 1);
	VERIFY(i.count() == 3);
	VERIFY(i.base() == a);
	VERIFY(hamon::move(i).base() == a);
	VERIFY(i.operator->() == a);
	VERIFY(*i == 42);
	VERIFY(&t6 == &i);
	VERIFY(i[0] == 42);
	VERIFY(i[1] == 2);
	VERIFY(i[2] == 3);
	auto i2 = i + 1;
	auto i3 = 2 + i;
	auto i4 = i3 - 1;
	VERIFY(*i2 == 2);
	VERIFY(i2.count() == 2);
	VERIFY(*i3 == 3);
	VERIFY(i3.count() == 1);
	VERIFY(*i4 == 2);
	VERIFY(i4.count() == 2);
	VERIFY(i - i2 == -1);
	VERIFY(i3 - i == 2);
	auto r = hamon::ranges::iter_move(i2);
	VERIFY(r == 2);
	VERIFY(a[0] == 42);
	VERIFY(a[1] == 2);
	VERIFY(a[2] == 3);
	VERIFY(a[3] == 4);
	VERIFY(a[4] == 5);
	hamon::ranges::iter_swap(i3, i4);
	VERIFY(a[0] == 42);
	VERIFY(a[1] == 3);
	VERIFY(a[2] == 2);
	VERIFY(a[3] == 4);
	VERIFY(a[4] == 5);

	hamon::counted_iterator<int const*> i5 = i;
	VERIFY(*i5 == 42);
	VERIFY(i5.count() == 3);

	i5 = i2;
	VERIFY(*i5 == 3);
	VERIFY(i5.count() == 2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5};
	input_iterator_wrapper<int> i{a};
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	auto ci = hamon::counted_iterator(i, 3);
#else
	auto ci = hamon::counted_iterator<input_iterator_wrapper<int>>(i, 3);
#endif
	using CI = decltype(ci);
	static_assert(hamon::same_as_t<decltype(hamon::declval<CI>()++), void>::value, "");
	VERIFY(ci.count() == 3);
	VERIFY(*ci == 1);
	VERIFY( (ci == CI(i, 3)));
	VERIFY(!(ci != CI(i, 3)));
	ci++;
	VERIFY(ci.count() == 2);
	VERIFY(*ci == 2);
	VERIFY(!(ci == CI(i, 3)));
	VERIFY( (ci != CI(i, 3)));
	return true;
}

GTEST_TEST(CountedIteratorTest, Test)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test02());
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool CompareTest()
{
	static_assert(has_eq  <hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");
	static_assert(has_neq <hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");
	static_assert(has_lt  <hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");
	static_assert(has_lteq<hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");
	static_assert(has_gt  <hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");
	static_assert(has_gteq<hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");

	static_assert(has_eq  <hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");
	static_assert(has_neq <hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");
	static_assert(has_lt  <hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");
	static_assert(has_lteq<hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");
	static_assert(has_gt  <hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");
	static_assert(has_gteq<hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");

	static_assert(!has_eq  <hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");
	static_assert(!has_neq <hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");
	static_assert(!has_lt  <hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");
	static_assert(!has_lteq<hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");
	static_assert(!has_gt  <hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");
	static_assert(!has_gteq<hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert( has_compare_three_way<hamon::counted_iterator<int*> const, hamon::counted_iterator<int*> const>::value, "");
	static_assert( has_compare_three_way<hamon::counted_iterator<int*> const, hamon::counted_iterator<int const*> const>::value, "");
	static_assert(!has_compare_three_way<hamon::counted_iterator<int*> const, hamon::counted_iterator<float*> const>::value, "");
#endif

	int a[] = {1, 2, 3, 4, 5};
	auto i1 = hamon::counted_iterator<int*>(a + 2, 3);
	auto i2 = hamon::counted_iterator<int*>(a + 2, 3);
	auto i3 = hamon::counted_iterator<int*>(a + 2, 3) + 1;
	auto i4 = hamon::counted_iterator<int*>(a + 2, 3) - 1;

	VERIFY( (i1 == i1));
	VERIFY( (i1 == i2));
	VERIFY(!(i1 == i3));
	VERIFY(!(i1 == i4));

	VERIFY(!(i1 != i1));
	VERIFY(!(i1 != i2));
	VERIFY( (i1 != i3));
	VERIFY( (i1 != i4));

	VERIFY(!(i1 < i1));
	VERIFY(!(i1 < i2));
	VERIFY( (i1 < i3));
	VERIFY(!(i1 < i4));

	VERIFY( (i1 <= i1));
	VERIFY( (i1 <= i2));
	VERIFY( (i1 <= i3));
	VERIFY(!(i1 <= i4));

	VERIFY(!(i1 > i1));
	VERIFY(!(i1 > i2));
	VERIFY(!(i1 > i3));
	VERIFY( (i1 > i4));

	VERIFY( (i1 >= i1));
	VERIFY( (i1 >= i2));
	VERIFY(!(i1 >= i3));
	VERIFY( (i1 >= i4));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY(hamon::is_eq(i1 <=> i1));
	VERIFY(hamon::is_eq(i1 <=> i2));
	VERIFY(hamon::is_lt(i1 <=> i3));
	VERIFY(hamon::is_gt(i1 <=> i4));
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(CountedIteratorTest, CompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest());
}

}	// namespace counted_iterator_test

}	// namespace hamon_iterator_test
