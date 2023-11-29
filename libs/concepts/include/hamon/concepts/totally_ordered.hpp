/**
 *	@file	totally_ordered.hpp
 *
 *	@brief	totally_ordered の定義
 */

#ifndef HAMON_CONCEPTS_TOTALLY_ORDERED_HPP
#define HAMON_CONCEPTS_TOTALLY_ORDERED_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/detail/partially_ordered_with.hpp>
#include <hamon/type_traits/conjunction.hpp>
#endif

namespace hamon
{

// 18.5.5 Concept totally_ordered	[concept.totallyordered]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::totally_ordered;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept totally_ordered =
	hamon::equality_comparable<T> &&
	detail::partially_ordered_with<T, T>;

#else

template <typename T>
using totally_ordered =
	hamon::conjunction<
		hamon::equality_comparable<T>,
		detail::partially_ordered_with<T, T>
	>;

#endif

template <typename T>
using totally_ordered_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::totally_ordered<T>>;
#else
	hamon::totally_ordered<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_TOTALLY_ORDERED_HPP
