/**
 *	@file	exchange.hpp
 *
 *	@brief	exchange を定義
 */

#ifndef HAMON_UTILITY_EXCHANGE_HPP
#define HAMON_UTILITY_EXCHANGE_HPP

#include <hamon/config.hpp>
#include <utility>

#if defined(__cpp_lib_exchange_function) && (__cpp_lib_exchange_function >= 201304) && \
	defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 201806) && \
    !(defined(_GLIBCXX_RELEASE) && (_GLIBCXX_RELEASE < 12)) && \
    !(defined(_LIBCPP_VERSION) && (_LIBCPP_VERSION < 14000)) && \
    !defined(HAMON_APPLE_CLANG)
// ※noexcept指定はP2401R0で追加されたが、defect fixなので__cpp_lib_exchange_functionの値は更新されなかった。

namespace hamon
{

using std::exchange;

}	// namespace hamon

#else

#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon
{

/**
 *	@brief	値を書き換え、書き換え前の値を返す
 *
 *	@tparam	T
 *	@tparam	U
 *
 *	T はムーブ構築可能でなければならない。
 *	U から T へムーブ代入可能でなければならない。
 *
 *	@param	obj			値を書き換えるオブジェクト
 *	@param	new_value	objに代入する値
 *
 *	@return	この関数を呼び出す前のobjの値を返す
 */
template <typename T, typename U = T>
inline HAMON_CXX14_CONSTEXPR T
exchange(T& obj, U&& new_value)
HAMON_NOEXCEPT_IF((
    hamon::is_nothrow_move_constructible<T>::value &&
    hamon::is_nothrow_assignable<T&, U>::value))
{
    T old_value = hamon::move(obj);
    obj = hamon::forward<U>(new_value);
    return old_value;
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_EXCHANGE_HPP
