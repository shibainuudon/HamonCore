/**
 *	@file	sorted_unique.hpp
 *
 *	@brief	sorted_unique の定義
 */

#ifndef HAMON_CONTAINER_SORTED_UNIQUE_HPP
#define HAMON_CONTAINER_SORTED_UNIQUE_HPP

#if defined(HAMON_USE_STD_FLAT_MAP) || defined(HAMON_USE_STD_FLAT_SET)

#if defined(HAMON_USE_STD_FLAT_MAP)
#include <flat_map>
#endif
#if defined(HAMON_USE_STD_FLAT_SET)
#include <flat_set>
#endif

namespace hamon
{

using std::sorted_unique_t;
using std::sorted_unique;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

// 23.6.7 Header <flat_map> synopsis[flat.map.syn]
// 23.6.10 Header <flat_set> synopsis[flat.set.syn]

struct sorted_unique_t { explicit sorted_unique_t() = default; };
HAMON_INLINE_VAR constexpr sorted_unique_t sorted_unique{};

}	// namespace hamon

#endif

#endif // HAMON_CONTAINER_SORTED_UNIQUE_HPP
