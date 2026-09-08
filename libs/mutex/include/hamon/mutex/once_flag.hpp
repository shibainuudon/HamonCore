/**
 *	@file	once_flag.hpp
 *
 *	@brief	once_flag の定義
 */

#ifndef HAMON_MUTEX_ONCE_FLAG_HPP
#define HAMON_MUTEX_ONCE_FLAG_HPP

#include <mutex>

namespace hamon
{

using std::once_flag;

#if 0	// TODO

// 32.6.7.1 Struct once_flag[thread.once.onceflag]

struct once_flag
{
	constexpr once_flag() noexcept;

	once_flag(const once_flag&) = delete;
	once_flag& operator=(const once_flag&) = delete;
};

#endif

}	// namespace hamon

#endif // HAMON_MUTEX_ONCE_FLAG_HPP
