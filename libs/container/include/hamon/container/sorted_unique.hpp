/**
 *	@file	sorted_unique.hpp
 *
 *	@brief	sorted_unique の定義
 */

#ifndef HAMON_CONTAINER_SORTED_UNIQUE_HPP
#define HAMON_CONTAINER_SORTED_UNIQUE_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 23.6.7 Header <flat_map> synopsis[flat.map.syn]
// 23.6.10 Header <flat_set> synopsis[flat.set.syn]

struct sorted_unique_t { explicit sorted_unique_t() = default; };
HAMON_INLINE_VAR constexpr sorted_unique_t sorted_unique{};

}	// namespace hamon

#endif // HAMON_CONTAINER_SORTED_UNIQUE_HPP
