/**
 *	@file	is_scalar.hpp
 *
 *	@brief	is_scalar の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SCALAR_HPP
#define HAMON_TYPE_TRAITS_IS_SCALAR_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_member_pointer.hpp>
#include <hamon/type_traits/is_null_pointer.hpp>
#include <hamon/config.hpp>

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
	: public hamon::disjunction<
		hamon::is_arithmetic<T>,
		hamon::is_enum<T>,
		hamon::is_pointer<T>,
		hamon::is_member_pointer<T>,
		hamon::is_null_pointer<T>
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_scalar_v = is_scalar<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SCALAR_HPP
