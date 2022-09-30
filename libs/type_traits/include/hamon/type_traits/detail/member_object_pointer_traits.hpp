/**
 *	@file	member_object_pointer_traits.hpp
 *
 *	@brief	member_object_pointer_traits の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_MEMBER_OBJECT_POINTER_TRAITS_HPP
#define HAMON_TYPE_TRAITS_DETAIL_MEMBER_OBJECT_POINTER_TRAITS_HPP

#include <hamon/preprocessor/empty.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
struct member_object_pointer_traits;

#define HAMON_MEMOBJPTR_TRAITS(CV_OPT)              \
template <typename R, typename T>	                \
struct member_object_pointer_traits<R T::* CV_OPT>	\
{	                                                \
	using result_type = R;	                        \
	using class_type = T;	                        \
}

HAMON_MEMOBJPTR_TRAITS(HAMON_PP_EMPTY());
HAMON_MEMOBJPTR_TRAITS(const);
HAMON_MEMOBJPTR_TRAITS(volatile);
HAMON_MEMOBJPTR_TRAITS(const volatile);

#undef HAMON_MEMOBJPTR_TRAITS

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_MEMBER_OBJECT_POINTER_TRAITS_HPP
