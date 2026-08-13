/**
 *	@file	is_object.hpp
 *
 *	@brief	is_object の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_OBJECT_HPP
#define HAMON_TYPE_TRAITS_IS_OBJECT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_function.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.3 Composite type traits

/**
 *	@brief	型Tがオブジェクト型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_objectは、型Tがオブジェクト型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	オブジェクト型は、スカラ型、配列型、共用型、クラス型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_object
	: public hamon::bool_constant<
		// 6.9.1 General[basic.types.general]/6
		// An object type is a (possibly cv-qualified) type that is
		// not a function type, not a reference type, and not cv void.
		!hamon::is_function_v<T> &&
		!hamon::is_reference_v<T> &&
		!hamon::is_void_v<T>
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_object_v = is_object<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_OBJECT_HPP
