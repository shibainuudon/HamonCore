/**
 *	@file	replace_first_arg.hpp
 *
 *	@brief	replace_first_arg を定義
 */

#ifndef HAMON_MEMORY_DETAIL_REPLACE_FIRST_ARG_HPP
#define HAMON_MEMORY_DETAIL_REPLACE_FIRST_ARG_HPP

namespace hamon
{

namespace detail
{

template <typename T, typename U>
struct replace_first_arg;

template <template <typename, typename...> class SomeTemplate, typename T, typename U, typename... Args>
struct replace_first_arg<SomeTemplate<T, Args...>, U>
{
	using type = SomeTemplate<U, Args...>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_REPLACE_FIRST_ARG_HPP
