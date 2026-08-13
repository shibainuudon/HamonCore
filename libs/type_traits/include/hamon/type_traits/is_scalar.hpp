/**
 *	@file	is_scalar.hpp
 *
 *	@brief	is_scalar の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SCALAR_HPP
#define HAMON_TYPE_TRAITS_IS_SCALAR_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_member_pointer.hpp>
#include <hamon/type_traits/is_null_pointer.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.3 Composite type traits

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
		// 6.9.1 General[basic.types.general]/7
		// Arithmetic types ([basic.fundamental]), enumeration types, pointer types,
		// pointer-to-member types ([basic.compound]), std​::​meta​::​​info, std​::​nullptr_t,
		// and cv-qualified versions of these types are collectively called scalar types.
		hamon::is_arithmetic_v<T> ||
		hamon::is_enum_v<T> ||
		hamon::is_pointer_v<T> ||
		hamon::is_member_pointer_v<T> ||
		//hamon::is_reflection_v<T> ||		// TODO
		hamon::is_null_pointer_v<T>
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_scalar_v = is_scalar<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SCALAR_HPP
