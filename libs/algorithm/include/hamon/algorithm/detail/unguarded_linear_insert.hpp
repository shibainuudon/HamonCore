/**
 *	@file	unguarded_linear_insert.hpp
 *
 *	@brief	unguarded_linear_insert の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_UNGUARDED_LINEAR_INSERT_HPP
#define HAMON_ALGORITHM_DETAIL_UNGUARDED_LINEAR_INSERT_HPP

#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
unguarded_linear_insert(RandomAccessIterator last, Compare comp)
{
	using value_t = hamon::iter_value_t<RandomAccessIterator>;
	value_t val = std::move(*last);
	auto next_it = last;
	--next_it;

	while (comp(val, *next_it))
	{
		*last = std::move(*next_it);
		last = next_it;
		--next_it;
	}

	*last = std::move(val);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_UNGUARDED_LINEAR_INSERT_HPP
