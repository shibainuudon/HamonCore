/**
 *	@file	is_copy_assignable.hpp
 *
 *	@brief	is_copy_assignable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
#define HAMON_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP

#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tがコピー代入可能かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_copy_assignableは、型Tがコピー代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	以下の条件がtrueである場合に、コピー代入が可能であると見なされる：
 *	・参照可能な型Tに対しては、is_assignable<T&, T const&>::value == trueと同じ結果となり、
 *	　それ以外はfalseと見なされる。
 *	・参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	  ・オブジェクト型
 *	  ・CV修飾されていない、もしくは参照修飾されていない関数型
 *	  ・参照修飾されている型
 */
template <typename T>
struct is_copy_assignable
	: public hamon::is_assignable<hamon::add_lvalue_reference_t<T>, hamon::add_lvalue_reference_t<hamon::add_const_t<T>>>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_copy_assignable_v = is_copy_assignable<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_COPY_ASSIGNABLE_HPP
