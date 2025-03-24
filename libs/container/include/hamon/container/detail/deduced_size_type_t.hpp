/**
 *	@file	deduced_size_type_t.hpp
 *
 *	@brief	deduced_size_type_t の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_DEDUCED_SIZE_TYPE_T_HPP
#define HAMON_CONTAINER_DETAIL_DEDUCED_SIZE_TYPE_T_HPP

#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [unord.map.overview]/5
// [unord.multimap.overview]/5
// [unord.set.overview]/5
// [unord.multiset.overview]
template <typename Allocator>
using deduced_size_type_t = typename hamon::allocator_traits<
	hamon::conditional_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		hamon::detail::simple_allocator<Allocator>,
#else
		hamon::detail::simple_allocator<Allocator>::value,
#endif
		Allocator,
		hamon::allocator<int>
	>
>::size_type;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_DEDUCED_SIZE_TYPE_T_HPP
