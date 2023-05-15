/**
 *	@file	adl_swap.hpp
 *
 *	@brief	adl_swap の定義
 */

#ifndef HAMON_UTILITY_ADL_SWAP_HPP
#define HAMON_UTILITY_ADL_SWAP_HPP

#include <hamon/utility/forward.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	必ずADL経由でswap関数を呼び出す
 *
 *	std::swap()とhamon::swap()があり、
 *	例えばstd::arrayとhamon::arrayで正しいswap関数を呼び出すには、
 *
 *	@code
 *	using std::swap;
 *	swap(a, b);
 *	@endcode
 *
 *	のようにusing宣言が必要となる。
 *	これは煩雑であるし間違いやすい、その上、conceptやSFINAEのときに
 *	書きづらいという問題があった。
 *	そこで、
 *	`hamon::adl_swap(a, b);`
 *	のように書くと、必ずADL経由で正しい方のswap関数を呼び出してくれるようにする。
 */

namespace adl_swap_detail
{

// "swap"という名前を導入する
using hamon::swap;


#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename T>
inline HAMON_CXX11_CONSTEXPR auto
adl_swap(T& a, T& b)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	// 名前空間修飾無しで呼び出す
	swap(a, b))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace adl_swap_detail

// hamon::adl_swapとして使えるようにする
using adl_swap_detail::adl_swap;

}	// namespace hamon

#endif // HAMON_UTILITY_ADL_SWAP_HPP
