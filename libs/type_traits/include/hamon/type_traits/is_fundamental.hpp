/**
 *	@file	is_fundamental.hpp
 *
 *	@brief	is_fundamental の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
#define HAMON_TYPE_TRAITS_IS_FUNDAMENTAL_HPP

#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_arithmetic.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/is_null_pointer.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	型Tが単純型(Fundamental types)か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_fundamentalは、型Tが単純型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	単純型は、算術型、void、nullptr_t、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_fundamental
	: public hamon::disjunction<
		hamon::is_arithmetic<T>,
		hamon::is_void<T>,
		hamon::is_null_pointer<T>
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_fundamental_v = is_fundamental<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_FUNDAMENTAL_HPP
