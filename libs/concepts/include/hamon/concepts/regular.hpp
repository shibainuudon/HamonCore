/**
 *	@file	regular.hpp
 *
 *	@brief	regular の定義
 */

#ifndef HAMON_CONCEPTS_REGULAR_HPP
#define HAMON_CONCEPTS_REGULAR_HPP

#include <hamon/concepts/config.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#endif

namespace hamon
{

#if defined(HAMON_USE_STD_CONCEPTS)

using std::regular;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept regular =
	hamon::semiregular<T> &&
	hamon::equality_comparable<T>;

#else

template <typename T>
using regular =
	hamon::conjunction<
		hamon::semiregular<T>,
		hamon::equality_comparable<T>
	>;

#endif

}	// namespace hamon

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using regular_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::regular<T>>;
#else
	hamon::regular<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_REGULAR_HPP
