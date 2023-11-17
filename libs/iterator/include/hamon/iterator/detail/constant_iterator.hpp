/**
 *	@file	constant_iterator.hpp
 *
 *	@brief	constant_iterator の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_CONSTANT_ITERATOR_HPP
#define HAMON_ITERATOR_DETAIL_CONSTANT_ITERATOR_HPP

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
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
using constant_iterator = hamon::conjunction<
	hamon::input_iterator_t<It>,
	hamon::same_as_t<hamon::iter_const_reference_t<It>, hamon::iter_reference_t<It>>>;

template <typename It>
using constant_iterator_t = constant_iterator<It>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_CONSTANT_ITERATOR_HPP
