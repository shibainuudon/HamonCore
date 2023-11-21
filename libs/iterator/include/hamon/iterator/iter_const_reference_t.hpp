/**
 *	@file	iter_const_reference_t.hpp
 *
 *	@brief	iter_const_reference_t の定義
 */

#ifndef HAMON_ITERATOR_ITER_CONST_REFERENCE_T_HPP
#define HAMON_ITERATOR_ITER_CONST_REFERENCE_T_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::iter_const_reference_t;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/common_reference.hpp>

namespace hamon
{

// 25.5.3.2 Alias templates[const.iterators.alias]
template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_readable, It)>
using iter_const_reference_t =
	hamon::common_reference_t<const hamon::iter_value_t<It>&&, hamon::iter_reference_t<It>>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITER_CONST_REFERENCE_T_HPP
