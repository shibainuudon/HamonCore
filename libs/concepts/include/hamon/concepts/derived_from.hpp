/**
 *	@file	derived_from.hpp
 *
 *	@brief	derived_from の定義
 */

#ifndef HAMON_CONCEPTS_DERIVED_FROM_HPP
#define HAMON_CONCEPTS_DERIVED_FROM_HPP

#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::derived_from;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <type_traits>

namespace hamon
{

template <typename Derived, typename Base>
concept derived_from =
	hamon::is_base_of<Base, Derived>::value &&
	std::is_convertible<Derived const volatile*, Base const volatile*>::value;

}	// namespace hamon

#else

#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/add_cv.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <type_traits>

namespace hamon
{

template <typename Derived, typename Base>
using derived_from =
	hamon::conjunction<
		hamon::is_base_of<Base, Derived>,
		std::is_convertible<
			hamon::add_pointer_t<hamon::add_cv_t<Derived>>,
			hamon::add_pointer_t<hamon::add_cv_t<Base>>
		>
	>;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Derived, typename Base>
using derived_from_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::derived_from<Derived, Base>>;
#else
	hamon::derived_from<Derived, Base>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_DERIVED_FROM_HPP
