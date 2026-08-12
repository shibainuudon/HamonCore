/**
 *	@file	is_member_function_pointer.hpp
 *
 *	@brief	is_member_function_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

namespace detail
{

template <typename T>
struct is_member_function_pointer_impl : public hamon::false_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...)> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) volatile> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const volatile> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...)> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) volatile> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const volatile> : public hamon::true_type{};

// reference qualified
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) &> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) volatile&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const volatile&> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) &> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) volatile&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const volatile&> : public hamon::true_type{};

// rvalue reference qualified
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) &&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const&&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) volatile&&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const volatile&&> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) &&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const&&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) volatile&&> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const volatile&&> : public hamon::true_type{};

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)
// noexcept
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) volatile noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const volatile noexcept> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) volatile noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const volatile noexcept> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) & noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) volatile& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const volatile& noexcept> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) & noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) volatile& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const volatile& noexcept> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) && noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const&& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) volatile&& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args...) const volatile&& noexcept> : public hamon::true_type{};

template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) && noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const&& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) volatile&& noexcept> : public hamon::true_type{};
template <typename T, typename U, typename... Args>
struct is_member_function_pointer_impl<T (U::*)(Args..., ...) const volatile&& noexcept> : public hamon::true_type{};
#endif

}	// namespace detail

/**
 *	@brief	型Tがメンバ関数へのポインタか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_function_pointerは、型Tがメンバ関数へのポインタであるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	データメンバへのポインタはメンバ関数へのポインタではない。
 *	staticなメンバ関数へのポインタはメンバ関数へのポインタではない。
 */
template <typename T>
struct is_member_function_pointer
	: public hamon::detail::is_member_function_pointer_impl<hamon::remove_cv_t<T>> {};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
