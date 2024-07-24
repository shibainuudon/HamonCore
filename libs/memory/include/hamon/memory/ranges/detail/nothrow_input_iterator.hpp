/**
 *	@file	nothrow_input_iterator.hpp
 *
 *	@brief	nothrow_input_iterator を定義
 */

#ifndef HAMON_MEMORY_RANGES_DETAIL_NOTHROW_INPUT_ITERATOR_HPP
#define HAMON_MEMORY_RANGES_DETAIL_NOTHROW_INPUT_ITERATOR_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.2 Special memory concepts[special.mem.concepts]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [special.mem.concepts]/2
template <typename I>
concept nothrow_input_iterator =
	hamon::input_iterator<I> &&
	hamon::is_lvalue_reference_v<hamon::iter_reference_t<I>> &&
	hamon::same_as<hamon::remove_cvref_t<hamon::iter_reference_t<I>>, hamon::iter_value_t<I>>;

#else

template <typename I>
using nothrow_input_iterator = hamon::conjunction<
	hamon::input_iterator<I>,
	hamon::is_lvalue_reference<hamon::iter_reference_t<I>>,
	hamon::same_as<hamon::remove_cvref_t<hamon::iter_reference_t<I>>, hamon::iter_value_t<I>>>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DETAIL_NOTHROW_INPUT_ITERATOR_HPP
