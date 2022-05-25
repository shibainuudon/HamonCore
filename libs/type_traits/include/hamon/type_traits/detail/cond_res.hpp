/**
 *	@file	cond_res.hpp
 *
 *	@brief	cond_res の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_COND_RES_HPP
#define HAMON_TYPE_TRAITS_DETAIL_COND_RES_HPP

#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>
#include <utility>

HAMON_WARNING_PUSH();

#if defined(HAMON_CLANG_VERSION) && (HAMON_CLANG_VERSION >= 100000)
HAMON_WARNING_DISABLE_CLANG("-Wdeprecated-volatile");
#endif

namespace hamon
{

namespace detail
{

#if !defined(_MSC_VER)

template <typename X, typename Y>
using cond_res = decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()());

#else

HAMON_WARNING_DISABLE_MSVC(4239);

template <typename X, typename Y, typename = void>
struct cond_res_impl_base {};

template <typename X, typename Y>
struct cond_res_impl_base<X, Y,
	hamon::void_t<decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()())>>
{
	using type = hamon::remove_cv_t<
		decltype(false ? std::declval<X(&)()>()() : std::declval<Y(&)()>()())
	>;
};

template <typename X, typename Y>
struct cond_res_impl
	: cond_res_impl_base<X, Y>
{};

template <typename X, typename Y>
struct cond_res_impl<X&, Y&&>
	: cond_res_impl_base<X, Y>
{};

template <typename X, typename Y>
struct cond_res_impl<X&&, Y&>
	: cond_res_impl_base<X, Y>
{};

template <typename X, typename Y>
using cond_res = typename cond_res_impl<X, Y>::type;

#endif

}	// namespace detail

}	// namespace hamon

HAMON_WARNING_POP();

#endif // HAMON_TYPE_TRAITS_DETAIL_COND_RES_HPP
