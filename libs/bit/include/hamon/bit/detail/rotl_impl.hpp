/**
 *	@file	rotl_impl.hpp
 *
 *	@brief	rotl_impl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_DETAIL_ROTL_IMPL_HPP
#define HAMON_BIT_DETAIL_ROTL_IMPL_HPP

#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR
T rotl_impl(T x, int N, int r) HAMON_NOEXCEPT
{
	return static_cast<T>((x << r) | (x >> (N - r)));
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIT_DETAIL_ROTL_IMPL_HPP
