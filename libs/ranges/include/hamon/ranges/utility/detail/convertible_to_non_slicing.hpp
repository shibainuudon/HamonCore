/**
 *	@file	convertible_to_non_slicing.hpp
 *
 *	@brief	convertible_to_non_slicing の定義
 */

#ifndef HAMON_RANGES_UTILITY_DETAIL_CONVERTIBLE_TO_NON_SLICING_HPP
#define HAMON_RANGES_UTILITY_DETAIL_CONVERTIBLE_TO_NON_SLICING_HPP

#include <hamon/ranges/utility/detail/uses_nonqualification_pointer_conversion.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept convertible_to_non_slicing =
	hamon::convertible_to<From, To> &&
	!uses_nonqualification_pointer_conversion<
		hamon::decay_t<From>,
		hamon::decay_t<To>>;

#else

template <typename From, typename To>
using convertible_to_non_slicing = hamon::conjunction<
	hamon::convertible_to<From, To>,
	hamon::negation<
		uses_nonqualification_pointer_conversion<
			hamon::decay_t<From>,
			hamon::decay_t<To>
		>
	>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DETAIL_CONVERTIBLE_TO_NON_SLICING_HPP
