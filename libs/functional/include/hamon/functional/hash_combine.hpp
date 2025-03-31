/**
 *	@file	hash_combine.hpp
 *
 *	@brief	hash_combine の定義
 */

#ifndef HAMON_FUNCTIONAL_HASH_COMBINE_HPP
#define HAMON_FUNCTIONAL_HASH_COMBINE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <hamon::size_t N = sizeof(hamon::size_t)>
struct do_hash_combine;

// sizeof(hamon::size_t) によって実際の処理を分岐
// 参考：
// https://github.com/HowardHinnant/hash_append/issues/7
// https://suzulang.com/cpp-64bit-hash-combine/

template <>
struct do_hash_combine<2>
{
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::size_t v1, hamon::size_t v2) const HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(v1 ^ (v2 + 0x9e37U + (v1 << 3) + (v1 >> 1)));
	}
};

template <>
struct do_hash_combine<4>
{
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::size_t v1, hamon::size_t v2) const HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(v1 ^ (v2 + 0x9e3779b9 + (v1 << 6) + (v1 >> 2)));
	}
};

template <>
struct do_hash_combine<8>
{
	HAMON_CXX11_CONSTEXPR hamon::size_t
	operator()(hamon::size_t v1, hamon::size_t v2) const HAMON_NOEXCEPT
	{
		return static_cast<hamon::size_t>(v1 ^ (v2 + 0x9e3779b97f4a7c15LLU + (v1 << 12) + (v1 >> 4)));
	}
};

}	// namespace detail

/**
 *	@brief	hash_combine
 *
 *	複数のハッシュ値を合わせて新しいハッシュ値を計算する
 */
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::size_t
hash_combine(hamon::size_t v1, hamon::size_t v2) HAMON_NOEXCEPT
{
	return detail::do_hash_combine<>{}(v1, v2);
}

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_HASH_COMBINE_HPP
