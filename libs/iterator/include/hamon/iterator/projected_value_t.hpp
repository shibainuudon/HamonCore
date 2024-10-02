/**
 *	@file	projected_value_t.hpp
 *
 *	@brief	projected_value_t の定義
 */

#ifndef HAMON_ITERATOR_PROJECTED_VALUE_T_HPP
#define HAMON_ITERATOR_PROJECTED_VALUE_T_HPP

#include <algorithm>

#if defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

namespace hamon
{

using std::projected_value_t;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/concepts/indirectly_regular_unary_invocable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

// [iterator.synopsis]

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::indirectly_readable I,
	hamon::indirectly_regular_unary_invocable<I> Proj
#else
	typename I,
	typename Proj
#endif
>
using projected_value_t =
	hamon::remove_cvref_t<hamon::invoke_result_t<Proj&, hamon::iter_value_t<I>&>>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_PROJECTED_VALUE_T_HPP
