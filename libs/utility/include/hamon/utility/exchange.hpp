/**
 *	@file	exchange.hpp
 *
 *	@brief	exchange を定義
 */

#ifndef HAMON_UTILITY_EXCHANGE_HPP
#define HAMON_UTILITY_EXCHANGE_HPP

#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.3 exchange[utility.exchange]

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
HAMON_CXX14_CONSTEXPR T
exchange(T& obj, U&& new_value)
HAMON_NOEXCEPT_IF((
    hamon::is_nothrow_move_constructible<T>::value &&	// [utility.exchange]/2
    hamon::is_nothrow_assignable<T&, U>::value))
{
	// [utility.exchange]/1
    T old_value = hamon::move(obj);
    obj = hamon::forward<U>(new_value);
    return old_value;
}

}	// namespace hamon

#endif // HAMON_UTILITY_EXCHANGE_HPP
