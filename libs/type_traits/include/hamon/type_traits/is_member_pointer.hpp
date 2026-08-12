/**
 *	@file	is_member_pointer.hpp
 *
 *	@brief	is_member_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_MEMBER_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

namespace detail
{

template <typename T>
struct is_member_pointer_impl : public hamon::false_type{};

template <typename T, typename U>
struct is_member_pointer_impl<T U::*> : public hamon::true_type{};
template <typename T, typename U>
struct is_member_pointer_impl<T U::* const> : public hamon::true_type{};
template <typename T, typename U>
struct is_member_pointer_impl<T U::* volatile> : public hamon::true_type{};
template <typename T, typename U>
struct is_member_pointer_impl<T U::* const volatile> : public hamon::true_type{};

}	// namespace detail

/**
 *	@brief	型Tがメンバポインタ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_pointerは、型Tがメンバポインタ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	メンバポインタ型は、データメンバへのポインタ型、
 *	メンバ関数へのポインタ型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_member_pointer
	: public hamon::detail::is_member_pointer_impl<hamon::remove_cv_t<T>> {};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_member_pointer_v = is_member_pointer<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
