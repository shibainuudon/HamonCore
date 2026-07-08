/**
 *	@file	derived_from.hpp
 *
 *	@brief	derived_from の定義
 */

#ifndef HAMON_CONCEPTS_DERIVED_FROM_HPP
#define HAMON_CONCEPTS_DERIVED_FROM_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/type_traits/add_cv.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#endif
#include <hamon/config.hpp>

namespace hamon
{

// 18.4.3 Concept derived_from	[concept.derived]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::derived_from;

#else

template <typename Derived, typename Base>
HAMON_CONCEPT_OR_BOOL derived_from =
	hamon::is_base_of<Base, Derived>::value &&
	hamon::is_convertible<
		hamon::add_pointer_t<hamon::add_cv_t<Derived>>,
		hamon::add_pointer_t<hamon::add_cv_t<Base>>
	>::value;

#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_DERIVED_FROM_HPP
