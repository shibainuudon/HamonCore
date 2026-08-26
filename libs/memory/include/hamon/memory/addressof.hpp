/**
 *	@file	addressof.hpp
 *
 *	@brief	addressof の定義
 */

#ifndef HAMON_MEMORY_ADDRESSOF_HPP
#define HAMON_MEMORY_ADDRESSOF_HPP

#include <hamon/memory/detail/addressof_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	変数のアドレスを必ず取得する
 *
 *	operator&をオーバーロードしたクラスであっても、そのオブジェクトのアドレスを取得できる。
 *
 *	operator&がオーバーロードされていない場合、constexprにできる。
 *	operator&がオーバーロードされている場合、constexprにできない。
 *	(C++17以降はstd::addressofがconstexprになるのでconstexprにできる)
 */
template <typename T>
HAMON_CXX11_CONSTEXPR T* addressof(T& r) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_addressof) || defined(HAMON_MSVC)
	return __builtin_addressof(r);
#else
	return detail::addressof_impl(r);
#endif
}

// [specialized.addressof], addressof
template <typename T>
const T* addressof(const T&&) = delete;

}	// namespace hamon

#endif // HAMON_MEMORY_ADDRESSOF_HPP
