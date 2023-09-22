/**
 *	@file	borrowed_range.hpp
 *
 *	@brief	borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_BORROWED_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/type_traits/conjunction.hpp>
#endif

namespace hamon
{
namespace ranges
{

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::borrowed_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept borrowed_range =
	ranges::range<T> &&
	detail::maybe_borrowed_range<T>;

#else

template <typename T>
using borrowed_range = hamon::conjunction<
	ranges::range<T>,
	detail::maybe_borrowed_range<T>
>;

#endif

template <typename T>
using borrowed_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::borrowed_range<T>>;
#else
	hamon::ranges::borrowed_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_BORROWED_RANGE_HPP
