/**
 *	@file	adl_get.hpp
 *
 *	@brief	adl_get の定義
 */

#ifndef HAMON_TUPLE_ADL_GET_HPP
#define HAMON_TUPLE_ADL_GET_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	必ずADL経由でget関数を呼び出す
 *
 *	std::get()とhamon::get()があり、
 *	例えばstd::tupleとhamon::tupleで正しいget関数を呼び出すには、
 *
 *	@code
 *	using std::get;
 *	get<I>(t);
 *	@endcode
 *
 *	のようにusing宣言が必要となる。
 *	これは煩雑であるし間違いやすい、その上、conceptやSFINAEのときに
 *	書きづらいという問題があった。
 *	`hamon::adl_get<I>(t);`
 *	のようにすると、必ずADL経由で正しい方のget関数を呼び出してくれる。
 */

namespace adl_get_detail
{

// "get"という名前を導入する
template <typename T>
void get(T) = delete;

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <hamon::size_t I, typename T>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR auto
adl_get(T&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	// 名前空間修飾無しで呼び出す
	get<I>(hamon::forward<T>(t)))

template <typename U, typename T>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR auto
adl_get(T&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	// 名前空間修飾無しで呼び出す
	get<U>(hamon::forward<T>(t)))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace adl_get_detail

// hamon::adl_getとして使えるようにする
using adl_get_detail::adl_get;

}	// namespace hamon

#endif // HAMON_TUPLE_ADL_GET_HPP
