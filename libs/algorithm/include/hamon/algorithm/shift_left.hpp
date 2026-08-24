/**
 *	@file	shift_left.hpp
 *
 *	@brief	shift_left の定義
 */

#ifndef HAMON_ALGORITHM_SHIFT_LEFT_HPP
#define HAMON_ALGORITHM_SHIFT_LEFT_HPP

#include <hamon/algorithm/move.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename ForwardIterator>
HAMON_CXX14_CONSTEXPR ForwardIterator
shift_left(ForwardIterator first, ForwardIterator last,
	typename hamon::iterator_traits<ForwardIterator>::difference_type n)
{
	if (n <= 0)
	{
		return last;
	}

	auto mid = ranges::next(first, n, last);
	if (mid == last)
	{
		return first;
	}

	return hamon::move(hamon::move(mid), hamon::move(last), hamon::move(first));
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_SHIFT_LEFT_HPP
