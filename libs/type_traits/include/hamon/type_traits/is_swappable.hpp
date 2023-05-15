/**
 *	@file	is_swappable.hpp
 *
 *	@brief	is_swappable の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SWAPPABLE_HPP
#define HAMON_TYPE_TRAITS_IS_SWAPPABLE_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_swappable) && (__cpp_lib_is_swappable >= 201603)

namespace hamon
{

using std::is_swappable;

}	// namespace hamon

#else

#include <hamon/utility/detail/is_swappable.hpp>

namespace hamon
{

/**
 *	@brief		型 T が Swap 可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_swappableは、型 T が Swappableコンセプトを満たしていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	参照可能な型に対して、is_swappable_with<T&, T&>::valueと同じ結果となり、参照可能でない型に対してはfalseとなる。
 *
 *	参照可能な型とは、以下のいずれかの条件に合致する型である：
 *	・オブジェクト型
 *	・CV修飾されていない、もしくは参照修飾されていない関数型
 *	・参照修飾されている型
 */
template <typename T>
struct is_swappable
	: public hamon::detail::is_swappable<T>
{};

}	// namespace hamon

#endif

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_swappable_v = is_swappable<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SWAPPABLE_HPP
