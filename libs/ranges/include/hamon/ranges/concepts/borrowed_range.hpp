/**
 *	@file	borrowed_range.hpp
 *
 *	@brief	borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_BORROWED_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#endif

namespace hamon
{
namespace ranges
{

// [range.range]/4

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::borrowed_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL borrowed_range =
	ranges::range<T> &&
	detail::maybe_borrowed_range<T>;

#else

template <typename T>
HAMON_CONCEPT_OR_BOOL borrowed_range =
	ranges::range<T>::value &&
	detail::maybe_borrowed_range<T>;

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_BORROWED_RANGE_HPP
