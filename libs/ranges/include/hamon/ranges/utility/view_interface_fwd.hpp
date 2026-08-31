/**
 *	@file	view_interface_fwd.hpp
 *
 *	@brief	ranges::view_interface の前方宣言
 */

#ifndef HAMON_RANGES_UTILITY_VIEW_INTERFACE_FWD_HPP
#define HAMON_RANGES_UTILITY_VIEW_INTERFACE_FWD_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <
	typename Derived
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename = hamon::enable_if_t<
		hamon::is_class<Derived>::value &&
		hamon::same_as<Derived, hamon::remove_cv_t<Derived>>
	>
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_class<Derived>::value && hamon::same_as<Derived, hamon::remove_cv_t<Derived>>
#endif
class view_interface;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_VIEW_INTERFACE_FWD_HPP
