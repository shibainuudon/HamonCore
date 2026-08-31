/**
 *	@file	from_range_t.hpp
 *
 *	@brief	from_range_t の定義
 */

#ifndef HAMON_RANGES_FROM_RANGE_T_HPP
#define HAMON_RANGES_FROM_RANGE_T_HPP

namespace hamon
{

// [ranges.syn]
struct from_range_t { explicit from_range_t() = default; };
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR from_range_t from_range{};

}	// namespace hamon

#endif // HAMON_RANGES_FROM_RANGE_T_HPP
