/**
 *	@file	get_deleter.hpp
 *
 *	@brief	get_deleter の定義
 */

#ifndef HAMON_MEMORY_GET_DELETER_HPP
#define HAMON_MEMORY_GET_DELETER_HPP

#include <hamon/memory/config.hpp>

#if defined(HAMON_USE_STD_SHARED_PTR)

namespace hamon
{

using std::get_deleter;

}	// namespace hamon

#else

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/detail/sp_access.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.3.2.2.11 get_deleter[util.smartptr.getdeleter]
template <typename D, typename T>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR D*	// nodiscard as an extension
get_deleter(shared_ptr<T> const& p) noexcept
{
	return hamon::detail::sp_access::get_deleter<D>(p);
}

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_GET_DELETER_HPP
