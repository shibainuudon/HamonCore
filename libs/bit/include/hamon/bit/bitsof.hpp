/**
 *	@file	bitsof.hpp
 *
 *	@brief	bitsof 関数テンプレートを定義
 */

#ifndef HAMON_BIT_BITSOF_HPP
#define HAMON_BIT_BITSOF_HPP

#include <hamon/config.hpp>
#include <climits>
#include <cstddef>

namespace hamon
{

/**
 *	@brief	型のビット数を取得する関数
 *
 *	コンパイラがconstexprに対応していた場合、コンパイル時定数を得ることができます。
 */
template <typename T>
inline HAMON_CONSTEXPR std::size_t
bitsof(void) HAMON_NOEXCEPT
{
	return sizeof(T) * CHAR_BIT;
}

/**
 *	@brief	型のビット数を取得する関数
 *
 *	引数から型を推測するバージョン
 */
template <typename T>
inline HAMON_CONSTEXPR std::size_t
bitsof(T const&) HAMON_NOEXCEPT
{
	return sizeof(T) * CHAR_BIT;
}

}	// namespace hamon

#endif // HAMON_BIT_BITSOF_HPP
