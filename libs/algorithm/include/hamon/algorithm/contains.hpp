/**
 *	@file	contains.hpp
 *
 *	@brief	contains の定義
 */

#ifndef HAMON_ALGORITHM_CONTAINS_HPP
#define HAMON_ALGORITHM_CONTAINS_HPP

#include <hamon/algorithm/find.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename InputIterator,
	typename T = typename hamon::iterator_traits<InputIterator>::value_type>
HAMON_CXX14_CONSTEXPR bool
contains(
	InputIterator first,
	InputIterator last,
	T const& value)
{
	return hamon::find(first, last, value) != last;
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_CONTAINS_HPP
