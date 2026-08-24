/**
 *	@file	sorted_equivalent.hpp
 *
 *	@brief	sorted_equivalent の定義
 */

#ifndef HAMON_CONTAINER_SORTED_EQUIVALENT_HPP
#define HAMON_CONTAINER_SORTED_EQUIVALENT_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 23.6.7 Header <flat_map> synopsis[flat.map.syn]
// 23.6.10 Header <flat_set> synopsis[flat.set.syn]

struct sorted_equivalent_t { explicit sorted_equivalent_t() = default; };
HAMON_INLINE_VAR constexpr sorted_equivalent_t sorted_equivalent{};

}	// namespace hamon

#endif // HAMON_CONTAINER_SORTED_EQUIVALENT_HPP
