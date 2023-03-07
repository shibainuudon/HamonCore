/**
 *	@file	iter_reference_t.hpp
 *
 *	@brief	iter_reference_t の定義
 */

#ifndef HAMON_ITERATOR_ITER_REFERENCE_T_HPP
#define HAMON_ITERATOR_ITER_REFERENCE_T_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::iter_reference_t;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/detail/dereferenceable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINED_PARAM(detail::dereferenceable, I)>
using iter_reference_t = decltype(*hamon::declval<I&>());

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITER_REFERENCE_T_HPP
