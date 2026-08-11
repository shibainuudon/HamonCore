/**
 *	@file	is_pointer.hpp
 *
 *	@brief	is_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

/**
 *	@brief	型Tがポインタ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_pointerは、型Tがポインタ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	関数へのポインタはポインタ型であるが、staticではないメンバへのポインタは、ポインタ型ではない。
 *	nullptrはポインタ型へ変換できるが，nullptr_t型はポインタ型ではない。
 */
template <typename T>
struct is_pointer : public hamon::false_type{};

template <typename T>
struct is_pointer<T*> : public hamon::true_type{};
template <typename T>
struct is_pointer<T* const> : public hamon::true_type{};
template <typename T>
struct is_pointer<T* volatile> : public hamon::true_type{};
template <typename T>
struct is_pointer<T* const volatile> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_pointer_v = is_pointer<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_POINTER_HPP
