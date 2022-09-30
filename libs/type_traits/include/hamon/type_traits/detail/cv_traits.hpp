/**
 *	@file	cv_traits.hpp
 *
 *	@brief	cv_traits の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_CV_TRAITS_HPP
#define HAMON_TYPE_TRAITS_DETAIL_CV_TRAITS_HPP

#include <hamon/type_traits/conditional.hpp>
#include <hamon/preprocessor/empty.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

struct cv_qualifier_none {};
struct cv_qualifier_const {};
struct cv_qualifier_volatile {};
struct cv_qualifier_cv {};

template <typename T, bool, bool>
struct cv_traits_impl;

template <typename T> struct cv_traits_impl<T, true,  true>  { using type = cv_qualifier_cv; };
template <typename T> struct cv_traits_impl<T, true,  false> { using type = cv_qualifier_const; };
template <typename T> struct cv_traits_impl<T, false, true>  { using type = cv_qualifier_volatile; };
template <typename T> struct cv_traits_impl<T, false, false> { using type = cv_qualifier_none; };

template <typename T>
struct cv_traits
{
	using type =
		typename cv_traits_impl<
			T,
			std::is_const<T>::value,
			std::is_volatile<T>::value
		>::type;
};

template <typename T>
using cv_traits_t = typename cv_traits<T>::type;

template <typename T>
struct member_function_cv_traits;

template <typename T>
using member_function_cv_traits_t = typename member_function_cv_traits<T>::type;


#define HAMON_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, EXCEPT) \
template <typename R, typename C, typename... Args>	                 \
struct member_function_cv_traits<                                    \
	R (C::* CV_OPT_1)(Args...) CV_OPT_2 EXCEPT>                      \
{	                                                                 \
	using type = T;	                                                 \
}

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

#define HAMON_MEM_FN_CV_TRAITS_IMPL(CV_OPT_1, CV_OPT_2, T)                  \
	HAMON_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, HAMON_PP_EMPTY()); \
	HAMON_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, noexcept)

#else

#define HAMON_MEM_FN_CV_TRAITS_IMPL(CV_OPT_1, CV_OPT_2, T)                  \
	HAMON_MEM_FN_CV_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2, T, HAMON_PP_EMPTY())

#endif

#define HAMON_MEM_FN_CV_TRAITS(CV_OPT)	                                          \
	HAMON_MEM_FN_CV_TRAITS_IMPL(CV_OPT, HAMON_PP_EMPTY(), cv_qualifier_none);     \
	HAMON_MEM_FN_CV_TRAITS_IMPL(CV_OPT, const,            cv_qualifier_const);    \
	HAMON_MEM_FN_CV_TRAITS_IMPL(CV_OPT,       volatile,   cv_qualifier_volatile); \
	HAMON_MEM_FN_CV_TRAITS_IMPL(CV_OPT, const volatile,   cv_qualifier_cv)


HAMON_MEM_FN_CV_TRAITS(HAMON_PP_EMPTY());
HAMON_MEM_FN_CV_TRAITS(const);
HAMON_MEM_FN_CV_TRAITS(volatile);
HAMON_MEM_FN_CV_TRAITS(const volatile);

#undef HAMON_MEM_FN_CV_TRAITS_IMPL_0
#undef HAMON_MEM_FN_CV_TRAITS_IMPL
#undef HAMON_MEM_FN_CV_TRAITS

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_CV_TRAITS_HPP
