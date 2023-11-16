/**
 *	@file	const_iterator.hpp
 *
 *	@brief	const_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONST_ITERATOR_HPP
#define HAMON_ITERATOR_CONST_ITERATOR_HPP

#include <hamon/iterator/basic_const_iterator.hpp>

#if defined(HAMON_USE_STD_BASIC_CONST_ITERATOR)

namespace hamon
{

using std::const_iterator;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [const.iterators.alias]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename It>
concept constant_iterator =
	hamon::input_iterator<It> &&
	hamon::same_as<hamon::iter_const_reference_t<It>, hamon::iter_reference_t<It>>;

template <typename It>
using constant_iterator_t = hamon::bool_constant<constant_iterator<It>>;

#else

template <typename It>
using constant_iterator_t = hamon::conjunction<
	hamon::input_iterator_t<It>,
	hamon::same_as_t<hamon::iter_const_reference_t<It>, hamon::iter_reference_t<It>>>;

#endif

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I)>
using const_iterator =
	hamon::conditional_t<
		detail::constant_iterator_t<I>::value,
		I,
		hamon::basic_const_iterator<I>
	>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_CONST_ITERATOR_HPP
