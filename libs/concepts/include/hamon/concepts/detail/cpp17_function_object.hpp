/**
 *	@file	cpp17_function_object.hpp
 *
 *	@brief	cpp17_function_object の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_FUNCTION_OBJECT_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_FUNCTION_OBJECT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename... Args>
concept cpp17_function_object =
	hamon::is_object_v<T> &&
	requires(T f, Args&&... args)
	{
		{ f(hamon::forward<Args>(args)...) };
	};

#else

template <typename T, typename... Args>
struct cpp17_function_object_impl
{
private:
	template <typename U, typename... UArgs,
		typename = hamon::enable_if_t<hamon::is_object<U>::value>,
		typename = decltype(hamon::declval<U>()(hamon::declval<UArgs>()...))
	>
	static auto test(int) -> hamon::true_type;

	template <typename U, typename... UArgs>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, Args...>(0));
};

template <typename T, typename... Args>
using cpp17_function_object =
	typename cpp17_function_object_impl<T, Args...>::type;

#endif

template <typename T, typename... Args>
using cpp17_function_object_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_function_object<T, Args...>>;
#else
	hamon::detail::cpp17_function_object<T, Args...>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_FUNCTION_OBJECT_HPP
