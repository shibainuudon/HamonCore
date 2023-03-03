/**
 *	@file	is_object.hpp
 *
 *	@brief	is_object の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_OBJECT_HPP
#define HAMON_TYPE_TRAITS_IS_OBJECT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

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
		std::is_object<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_object_v = is_object<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_OBJECT_HPP
