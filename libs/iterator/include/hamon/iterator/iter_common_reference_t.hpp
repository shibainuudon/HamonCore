/**
 *	@file	iter_common_reference_t.hpp
 *
 *	@brief	iter_common_reference_t の定義
 */

#ifndef HAMON_ITERATOR_ITER_COMMON_REFERENCE_T_HPP
#define HAMON_ITERATOR_ITER_COMMON_REFERENCE_T_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::iter_common_reference_t;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/detail/indirect_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINED_PARAM(hamon::indirectly_readable, T)>
using iter_common_reference_t =
	hamon::common_reference_t<hamon::iter_reference_t<T>, hamon::detail::indirect_value_t<T>>;

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_ITER_COMMON_REFERENCE_T_HPP
