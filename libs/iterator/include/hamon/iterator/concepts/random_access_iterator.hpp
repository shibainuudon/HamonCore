/**
 *	@file	random_access_iterator.hpp
 *
 *	@brief	random_access_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP

#include <hamon/iterator/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES_ITERATOR)
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/detail/iter_concept.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

using std::random_access_iterator;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept random_access_iterator =
	hamon::bidirectional_iterator<Iter> &&
	hamon::derived_from<hamon::detail::iter_concept<Iter>, hamon::random_access_iterator_tag> &&
	hamon::totally_ordered<Iter> &&
	hamon::sized_sentinel_for<Iter, Iter> &&
	requires(Iter i, Iter const j, hamon::iter_difference_t<Iter> const n)
	{
		{ i += n } -> hamon::same_as<Iter&>;
		{ j +  n } -> hamon::same_as<Iter>;
		{ n +  j } -> hamon::same_as<Iter>;
		{ i -= n } -> hamon::same_as<Iter&>;
		{ j -  n } -> hamon::same_as<Iter>;
		{  j[n]  } -> hamon::same_as<hamon::iter_reference_t<Iter>>;
	};

#else

namespace detail
{

template <typename Iter>
struct random_access_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::bidirectional_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::derived_from<
			hamon::detail::iter_concept<I2>, hamon::random_access_iterator_tag>::value>,
		typename = hamon::enable_if_t<hamon::totally_ordered<I2>::value>,
		typename = hamon::enable_if_t<hamon::sized_sentinel_for<I2, I2>::value>,
#if defined(HAMON_MSVC) && (HAMON_MSVC < 1920)
		typename J2 = I2,
#else
		typename J2 = I2 const,
#endif
		typename D = hamon::iter_difference_t<I2> const,
		typename T1 = decltype(hamon::declval<I2&>() += hamon::declval<D >()),
		typename T2 = decltype(hamon::declval<J2 >() +  hamon::declval<D >()),
		typename T3 = decltype(hamon::declval<D  >() +  hamon::declval<J2>()),
		typename T4 = decltype(hamon::declval<I2&>() -= hamon::declval<D >()),
		typename T5 = decltype(hamon::declval<J2 >() -  hamon::declval<D >()),
		typename T6 = decltype(hamon::declval<J2 >()[hamon::declval<D>()])
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<T1, I2&>,
		hamon::same_as<T2, I2>,
		hamon::same_as<T3, I2>,
		hamon::same_as<T4, I2&>,
		hamon::same_as<T5, I2>,
		hamon::same_as<T6, hamon::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using random_access_iterator =
	typename detail::random_access_iterator_impl<Iter>::type;

#endif

template <typename Iter>
using random_access_iterator_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::random_access_iterator<Iter>>;
#else
	hamon::random_access_iterator<Iter>;
#endif

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_RANDOM_ACCESS_ITERATOR_HPP
