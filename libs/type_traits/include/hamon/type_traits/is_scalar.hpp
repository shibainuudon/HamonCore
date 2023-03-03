/**
 *	@file	is_scalar.hpp
 *
 *	@brief	is_scalar の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SCALAR_HPP
#define HAMON_TYPE_TRAITS_IS_SCALAR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがスカラ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_scalarは、型Tがスカラ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	スカラ型は、算術型、列挙型、ポインタ型、メンバポインタ型、nullptr_t、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_scalar
	: public hamon::bool_constant<
		std::is_scalar<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_scalar_v = is_scalar<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SCALAR_HPP
