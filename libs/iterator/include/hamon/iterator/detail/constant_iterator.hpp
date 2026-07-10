/**
 *	@file	constant_iterator.hpp
 *
 *	@brief	constant_iterator の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_CONSTANT_ITERATOR_HPP
#define HAMON_ITERATOR_DETAIL_CONSTANT_ITERATOR_HPP

#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [const.iterators.alias]

template <typename It>
HAMON_CONCEPT_OR_BOOL constant_iterator =
	hamon::input_iterator<It> &&
	hamon::same_as<hamon::iter_const_reference_t<It>, hamon::iter_reference_t<It>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_CONSTANT_ITERATOR_HPP
