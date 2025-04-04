﻿/**
 *	@file	hash_combine.hpp
 *
 *	@brief	hash_combine
 */

#ifndef HAMON_FUNCTIONAL_HASH_COMBINE_HPP
#define HAMON_FUNCTIONAL_HASH_COMBINE_HPP

#include <hamon/functional/ranges/hash.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

namespace detail
{

template <typename Hash, hamon::size_t N = sizeof(hamon::size_t)>
struct do_hash_combine;

// sizeof(hamon::size_t) によって実際の処理を分岐
// 参考：
// https://github.com/HowardHinnant/hash_append/issues/7
// https://suzulang.com/cpp-64bit-hash-combine/

template <typename Hash>
struct do_hash_combine<Hash, 2>
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::size_t seed, T const& v) const HAMON_NOEXCEPT
	{
		return seed ^ (Hash{}(v) + 0x9e37U + (seed << 3) + (seed >> 1));
	}
};

template <typename Hash>
struct do_hash_combine<Hash, 4>
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::size_t seed, T const& v) const HAMON_NOEXCEPT
	{
		return seed ^ (Hash{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
	}
};

template <typename Hash>
struct do_hash_combine<Hash, 8>
{
	template <typename T>
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::size_t seed, T const& v) const HAMON_NOEXCEPT
	{
		return seed ^ (Hash{}(v) + 0x9e3779b97f4a7c15LLU + (seed << 12) + (seed >> 4));
	}
};

inline HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine_impl(hamon::size_t seed) HAMON_NOEXCEPT
{
	return seed;
}

template <typename T, typename... Rest>
inline HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine_impl(hamon::size_t seed, T const& v, Rest const&... rest) HAMON_NOEXCEPT
{
	return hash_combine_impl(do_hash_combine<hamon::ranges::hash_t>{}(seed, v), rest...);
}

}	// namespace detail

/**
 *	@brief	hash_combine
 *
 *	複数の値からハッシュ値を計算する
 */
template <typename... T>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine(hamon::size_t seed, T const&... args) HAMON_NOEXCEPT
{
	return detail::hash_combine_impl(seed, args...);
}

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_FUNCTIONAL_HASH_COMBINE_HPP
