/**
 *	@file	rel_to_abs.hpp
 *
 *	@brief	rel_to_abs の定義
 */

#ifndef HAMON_CONDITION_VARIABLE_DETAIL_REL_TO_ABS_HPP
#define HAMON_CONDITION_VARIABLE_DETAIL_REL_TO_ABS_HPP

#include <hamon/chrono.hpp>

namespace hamon
{

namespace detail
{

// [thread.condition.general]/6

template <typename Dur>
inline chrono::steady_clock::time_point
rel_to_abs(Dur const& rel_time)
{
	return chrono::steady_clock::now() + chrono::ceil<chrono::steady_clock::duration>(rel_time);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONDITION_VARIABLE_DETAIL_REL_TO_ABS_HPP
