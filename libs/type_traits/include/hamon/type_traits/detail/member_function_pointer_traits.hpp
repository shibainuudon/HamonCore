/**
 *	@file	member_function_pointer_traits.hpp
 *
 *	@brief	member_function_pointer_traits の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_MEMBER_FUNCTION_POINTER_TRAITS_HPP
#define HAMON_TYPE_TRAITS_DETAIL_MEMBER_FUNCTION_POINTER_TRAITS_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/preprocessor/empty.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace detail
{

namespace memfun_traits_detail
{

template <typename R, typename T, typename... Args>
struct memfun_traits_base
{
	using result_type = R;
	using class_type = T;
	using arity = hamon::integral_constant<std::size_t, sizeof...(Args)>;
};

template <typename F>
struct memfun_traits_impl;

#define HAMON_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2)            \
template <typename R, typename T, typename... Args>	                 \
struct memfun_traits_impl<R (T::* CV_OPT_1)(Args...) CV_OPT_2>       \
: public memfun_traits_base< R, T CV_OPT_1, Args...>                 \
{	                                                                 \
	using vararg = hamon::false_type;                                \
};                                                                   \
template <typename R, typename T, typename... Args>	                 \
struct memfun_traits_impl< R (T::* CV_OPT_1)(Args..., ...) CV_OPT_2> \
: public memfun_traits_base< R, T CV_OPT_1, Args...>                 \
{	                                                                 \
	using vararg = hamon::true_type;                                 \
}

#if defined(HAMON_HAS_CXX17_NOEXCEPT_FUNCTION_TYPE)

#define HAMON_MEMFUNPTR_TRAITS_IMPL_1(CV_OPT_1, CV_OPT_2) \
	HAMON_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2);    \
	HAMON_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2 noexcept)

#else

#define HAMON_MEMFUNPTR_TRAITS_IMPL_1(CV_OPT_1, CV_OPT_2) \
	HAMON_MEMFUNPTR_TRAITS_IMPL_0(CV_OPT_1, CV_OPT_2)

#endif

#define HAMON_MEMFUNPTR_TRAITS_IMPL_2(CV_OPT_1, CV_OPT_2) \
	HAMON_MEMFUNPTR_TRAITS_IMPL_1(CV_OPT_1, CV_OPT_2);    \
	HAMON_MEMFUNPTR_TRAITS_IMPL_1(CV_OPT_1, CV_OPT_2 &);  \
	HAMON_MEMFUNPTR_TRAITS_IMPL_1(CV_OPT_1, CV_OPT_2 &&)


#define HAMON_MEMFUNPTR_TRAITS(CV_OPT)                          \
	HAMON_MEMFUNPTR_TRAITS_IMPL_2(CV_OPT, HAMON_PP_EMPTY());	\
	HAMON_MEMFUNPTR_TRAITS_IMPL_2(CV_OPT, const);	            \
	HAMON_MEMFUNPTR_TRAITS_IMPL_2(CV_OPT, volatile);	        \
	HAMON_MEMFUNPTR_TRAITS_IMPL_2(CV_OPT, const volatile)

HAMON_MEMFUNPTR_TRAITS(HAMON_PP_EMPTY());
HAMON_MEMFUNPTR_TRAITS(const);
HAMON_MEMFUNPTR_TRAITS(volatile);
HAMON_MEMFUNPTR_TRAITS(const volatile);

#undef HAMON_MEMFUNPTR_TRAITS_IMPL_0
#undef HAMON_MEMFUNPTR_TRAITS_IMPL_1
#undef HAMON_MEMFUNPTR_TRAITS_IMPL_2
#undef HAMON_MEMFUNPTR_TRAITS

}	// namespace memfun_traits_detail

template <typename F>
struct member_function_pointer_traits
	: public memfun_traits_detail::memfun_traits_impl<F>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_MEMBER_FUNCTION_POINTER_TRAITS_HPP
