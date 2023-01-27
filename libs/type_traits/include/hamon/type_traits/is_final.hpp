/**
 *	@file	is_final.hpp
 *
 *	@brief	is_final の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_FINAL_HPP
#define HAMON_TYPE_TRAITS_IS_FINAL_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_final) && (__cpp_lib_is_final >= 201402)

namespace hamon
{

using std::is_final;

}	// namespace hamon

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__is_final)

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

/**
 *	@brief	型Tにfinalが付いているかを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tがクラス型である場合、その型は完全型でなければならない
 *
 *	is_finalは、型Tがfinal指定されていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_final
	: public hamon::bool_constant<__is_final(T)>
{};

}	// namespace hamon

#else
#  define HAMON_NO_IS_FINAL
#endif

#if !defined(HAMON_NO_IS_FINAL)

#define HAMON_HAS_IS_FINAL

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_final_v = is_final<T>::value;
#endif

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_FINAL_HPP
