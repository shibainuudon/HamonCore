/**
 *	@file	is_trivially_move_assignable.hpp
 *
 *	@brief	is_trivially_move_assignable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP
#define HAMON_TYPE_TRAITS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP

#include <hamon/type_traits/add_lvalue_reference.hpp>
#include <hamon/type_traits/add_rvalue_reference.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief	型Tがトリビアルにムーブ代入可能か調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_trivially_move_assignableは、型Tがトリビアルにムーブ代入可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	以下の条件がtrueである場合に、トリビアルにムーブ代入可能であると見なされる：
 *	・参照可能な型Tに対しては、is_trivially_assignable<T&, T&&>::value == trueと同じ結果となり、
 *	　それ以外はfalseと見なされる。
 *	・参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	  ・オブジェクト型
 *	  ・CV修飾されていない、もしくは参照修飾されていない関数型
 *	  ・参照修飾されている型
 */
template <typename T>
struct is_trivially_move_assignable
	: public hamon::is_trivially_assignable<hamon::add_lvalue_reference_t<T>, hamon::add_rvalue_reference_t<T>>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_TRIVIALLY_MOVE_ASSIGNABLE_HPP
