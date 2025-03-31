/**
 *	@file	hash_combine.hpp
 *
 *	@brief	hash_combine
 */

#ifndef HAMON_FUNCTIONAL_RANGES_HASH_COMBINE_HPP
#define HAMON_FUNCTIONAL_RANGES_HASH_COMBINE_HPP

#include <hamon/functional/hash_combine.hpp>
#include <hamon/functional/ranges/hash.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

namespace detail
{

inline HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine_impl(hamon::size_t seed) HAMON_NOEXCEPT
{
	return seed;
}

template <typename T, typename... Rest>
inline HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine_impl(hamon::size_t seed, T const& v, Rest const&... rest) HAMON_NOEXCEPT
{
	return hash_combine_impl(hamon::hash_combine(seed, hamon::ranges::hash(v)), rest...);
}

}	// namespace detail

/**
 *	@brief	hash_combine
 *
 *	複数の値からハッシュ値を計算する
 */
template <typename... T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine(hamon::size_t seed, T const&... args) HAMON_NOEXCEPT
{
	return detail::hash_combine_impl(seed, args...);
}

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_FUNCTIONAL_RANGES_HASH_COMBINE_HPP
