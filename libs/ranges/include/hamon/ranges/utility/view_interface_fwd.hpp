/**
 *	@file	view_interface_fwd.hpp
 *
 *	@brief	ranges::view_interface の前方宣言
 */

#ifndef HAMON_RANGES_UTILITY_VIEW_INTERFACE_FWD_HPP
#define HAMON_RANGES_UTILITY_VIEW_INTERFACE_FWD_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::view_interface;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_class.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <
	typename Derived
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, typename = hamon::enable_if_t<
		hamon::conjunction<
			hamon::is_class<Derived>,
			hamon::same_as<Derived, hamon::remove_cv_t<Derived>>
		>::value
	>
#endif
>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_class<Derived>::value && hamon::same_as<Derived, hamon::remove_cv_t<Derived>>
#endif
class view_interface;

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_UTILITY_VIEW_INTERFACE_FWD_HPP
