/**
 *	@file	cv_bool.hpp
 *
 *	@brief	cv_bool の定義
 */

#ifndef HAMON_RANGES_DETAIL_CV_BOOL_HPP
#define HAMON_RANGES_DETAIL_CV_BOOL_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cv_bool = hamon::same_as<const volatile T, const volatile bool>;

#else

template <typename T>
using cv_bool = hamon::same_as<const volatile T, const volatile bool>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_CV_BOOL_HPP
