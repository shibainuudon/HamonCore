/**
 *	@file	pair_get.hpp
 *
 *	@brief	pair_get の定義
 */

#ifndef HAMON_PAIR_DETAIL_PAIR_GET_HPP
#define HAMON_PAIR_DETAIL_PAIR_GET_HPP

#include <hamon/pair/pair_fwd.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace pair_detail
{

template <hamon::size_t I>
struct pair_get;

// [pair.astuple]/4.1
template <>
struct pair_get<0>
{
    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1&
    get(pair<T1, T2>& p) HAMON_NOEXCEPT
	{
		return p.first;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1 const&
    get(pair<T1, T2> const& p) HAMON_NOEXCEPT
	{
		return p.first;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1&&
    get(pair<T1, T2>&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T1>(p.first);
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T1 const&&
    get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T1 const>(p.first);
	}
};

// [pair.astuple]/4.2
template <>
struct pair_get<1>
{
    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2&
    get(pair<T1, T2>& p) HAMON_NOEXCEPT
	{
		return p.second;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2 const&
    get(pair<T1, T2> const& p) HAMON_NOEXCEPT
	{
		return p.second;
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2&&
    get(pair<T1, T2>&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T2>(p.second);
	}

    template <typename T1, typename T2>
    static HAMON_CXX11_CONSTEXPR T2 const&&
    get(pair<T1, T2> const&& p) HAMON_NOEXCEPT
	{
		return hamon::forward<T2 const>(p.second);
	}
};

}	// namespace pair_detail

}	// namespace hamon

#endif // HAMON_PAIR_DETAIL_PAIR_GET_HPP
