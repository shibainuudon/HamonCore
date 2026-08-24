/**
 *	@file	hive_fwd.hpp
 *
 *	@brief	hive の前方宣言
 */

#ifndef HAMON_HIVE_HIVE_FWD_HPP
#define HAMON_HIVE_HIVE_FWD_HPP

#include <hamon/memory/allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>

namespace hamon
{

// 23.3.8 Header <hive> synopsis[hive.syn]

template <typename T, typename Allocator = hamon::allocator<T>>
class hive;

namespace pmr {

template <typename T>
using hive = hamon::hive<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr

}	// namespace hamon

#endif // HAMON_HIVE_HIVE_FWD_HPP
