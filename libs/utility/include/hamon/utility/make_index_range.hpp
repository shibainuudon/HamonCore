/**
 *	@file	make_index_range.hpp
 *
 *	@brief	make_index_range を定義
 */

#ifndef HAMON_UTILITY_MAKE_INDEX_RANGE_HPP
#define HAMON_UTILITY_MAKE_INDEX_RANGE_HPP

#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_integer_range.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// [N, M) のindex_sequenceを得る
template <hamon::size_t N, hamon::size_t M>
using make_index_range = hamon::make_integer_range<hamon::size_t, N, M>;

}	// namespace hamon

#endif // HAMON_UTILITY_MAKE_INDEX_RANGE_HPP
