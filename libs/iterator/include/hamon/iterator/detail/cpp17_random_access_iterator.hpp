/**
 *	@file	cpp17_random_access_iterator.hpp
 *
 *	@brief	cpp17_random_access_iterator の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_CPP17_RANDOM_ACCESS_ITERATOR_HPP
#define HAMON_ITERATOR_DETAIL_CPP17_RANDOM_ACCESS_ITERATOR_HPP

#include <hamon/iterator/detail/cpp17_bidirectional_iterator.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [iterator.traits]/2

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept cpp17_random_access_iterator =
	cpp17_bidirectional_iterator<I> &&
	hamon::totally_ordered<I> &&
	requires(I i, typename hamon::incrementable_traits<I>::difference_type n)
	{
		{ i += n } -> hamon::same_as<I&>;
		{ i -= n } -> hamon::same_as<I&>;
		{ i +  n } -> hamon::same_as<I>;
		{ n +  i } -> hamon::same_as<I>;
		{ i -  n } -> hamon::same_as<I>;
		{ i - i } -> hamon::same_as<decltype(n)>;
		{  i[n]  } -> hamon::convertible_to<hamon::iter_reference_t<I>>;
	};

template <typename T>
using cpp17_random_access_iterator_t = hamon::bool_constant<cpp17_random_access_iterator<T>>;

#else

namespace cpp17_random_access_iterator_detail
{

template <typename I>
struct cpp17_random_access_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_bidirectional_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::totally_ordered<I2>::value>,
		typename D = typename hamon::incrementable_traits<I2>::difference_type,
		typename T1 = decltype(hamon::declval<I2&>() += hamon::declval<D& >()),
		typename T2 = decltype(hamon::declval<I2&>() -= hamon::declval<D& >()),
		typename T3 = decltype(hamon::declval<I2&>() +  hamon::declval<D& >()),
		typename T4 = decltype(hamon::declval<D& >() +  hamon::declval<I2&>()),
		typename T5 = decltype(hamon::declval<I2&>() -  hamon::declval<D& >()),
		typename T6 = decltype(hamon::declval<I2&>() -  hamon::declval<I2&>()),
		typename T7 = decltype(hamon::declval<I2&>()[hamon::declval<D&>()])
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<T1, I2&>,
		hamon::same_as<T2, I2&>,
		hamon::same_as<T3, I2>,
		hamon::same_as<T4, I2>,
		hamon::same_as<T5, I2>,
		hamon::same_as<T6, D>,
		hamon::convertible_to<T7, hamon::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

}	// namespace cpp17_random_access_iterator_detail

template <typename I>
using cpp17_random_access_iterator =
	typename cpp17_random_access_iterator_detail::cpp17_random_access_iterator_impl<I>::type;

template <typename T>
using cpp17_random_access_iterator_t = cpp17_random_access_iterator<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_CPP17_RANDOM_ACCESS_ITERATOR_HPP
