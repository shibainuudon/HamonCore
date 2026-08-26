/**
 *	@file	iter_reference_t.hpp
 *
 *	@brief	iter_reference_t の定義
 */

#ifndef HAMON_ITERATOR_ITER_REFERENCE_T_HPP
#define HAMON_ITERATOR_ITER_REFERENCE_T_HPP

#include <hamon/iterator/detail/dereferenceable.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINT(detail::dereferenceable, I)>
using iter_reference_t = decltype(*hamon::declval<I&>());

}	// namespace hamon

#endif // HAMON_ITERATOR_ITER_REFERENCE_T_HPP
