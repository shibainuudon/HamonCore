/**
 *	@file	uses_nonqualification_pointer_conversion.hpp
 *
 *	@brief	uses_nonqualification_pointer_conversion の定義
 */

#ifndef HAMON_RANGES_UTILITY_DETAIL_USES_NONQUALIFICATION_POINTER_CONVERSION_HPP
#define HAMON_RANGES_UTILITY_DETAIL_USES_NONQUALIFICATION_POINTER_CONVERSION_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept uses_nonqualification_pointer_conversion =
	hamon::is_pointer<From>::value &&
	hamon::is_pointer<To>::value &&
	!hamon::convertible_to<
		hamon::remove_pointer_t<From>(*)[],
		hamon::remove_pointer_t<To>(*)[]
	>;

#else

template <typename From, typename To>
using uses_nonqualification_pointer_conversion = hamon::conjunction<
	hamon::is_pointer<From>,
	hamon::is_pointer<To>,
	hamon::negation<
		hamon::convertible_to<
			hamon::remove_pointer_t<From>(*)[],
			hamon::remove_pointer_t<To>(*)[]
		>
	>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_USES_NONQUALIFICATION_POINTER_CONVERSION_HPP
