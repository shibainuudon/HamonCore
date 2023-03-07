/**
 *	@file	overload_priority.hpp
 *
 *	@brief	overload_priority の定義
 */

#ifndef HAMON_DETAIL_OVERLOAD_PRIORITY_HPP
#define HAMON_DETAIL_OVERLOAD_PRIORITY_HPP

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

namespace detail
{

template <hamon::size_t N>
struct overload_priority : public overload_priority<N - 1>
{};

template <>
struct overload_priority<0>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_DETAIL_OVERLOAD_PRIORITY_HPP
