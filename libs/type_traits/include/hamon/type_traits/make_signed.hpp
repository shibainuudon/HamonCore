/**
 *	@file	make_signed.hpp
 *
 *	@brief	make_signed の定義
 */

#ifndef HAMON_TYPE_TRAITS_MAKE_SIGNED_HPP
#define HAMON_TYPE_TRAITS_MAKE_SIGNED_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief	整数型を符号付きにする。
 *
 *	@tparam		T
 *
 *	@require	型Tが、整数型もしくは列挙型(cv修飾を許容する)であること。ただしboolは許可されない。
 *
 *	make_signedは、型Tに対応する符号付き整数型を、メンバ型typeとして定義する。
 *	型Tがcv修飾されていた場合は、メンバ型typeにも同じcv修飾が付加される。
 */
using std::make_signed;

template <typename T>
using make_signed_t = typename make_signed<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_MAKE_SIGNED_HPP
