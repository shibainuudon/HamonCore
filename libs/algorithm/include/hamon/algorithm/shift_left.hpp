/**
 *	@file	shift_left.hpp
 *
 *	@brief	shift_left の定義
 */

#ifndef HAMON_ALGORITHM_SHIFT_LEFT_HPP
#define HAMON_ALGORITHM_SHIFT_LEFT_HPP

#include <hamon/config.hpp>
#include <algorithm>

#if defined(__cpp_lib_shift) && (__cpp_lib_shift >= 201806) &&	\
	!(defined(HAMON_APPLE_CLANG) && (HAMON_APPLE_CLANG <= 130000))

namespace hamon
{

using std::shift_left;

}	// namespace hamon

#else

#include <hamon/algorithm/move.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <utility>

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

	return hamon::move(std::move(mid), std::move(last), std::move(first));
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SHIFT_LEFT_HPP
