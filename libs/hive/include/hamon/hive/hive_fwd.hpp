/**
 *	@file	hive_fwd.hpp
 *
 *	@brief	hive の前方宣言
 */

#ifndef HAMON_HIVE_HIVE_FWD_HPP
#define HAMON_HIVE_HIVE_FWD_HPP

#include <hamon/hive/config.hpp>

#if defined(HAMON_USE_STD_HIVE)

#include <hive>

namespace hamon
{

using std::hive_limits;
using std::hive;

}	// namespace hamon

#else

#include <hamon/memory/allocator.hpp>

namespace hamon
{

struct hive_limits;

template <typename T, typename Allocator = hamon::allocator<T>>
class hive;

}	// namespace hamon

#endif

#endif // HAMON_HIVE_HIVE_FWD_HPP
