/**
 *	@file	invoke.hpp
 *
 *	@brief	invoke 関数の定義
 */

#ifndef HAMON_FUNCTIONAL_INVOKE_HPP
#define HAMON_FUNCTIONAL_INVOKE_HPP

#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_INVOKE)

namespace hamon
{

using std::invoke;

}	// namespace hamon

#else

#include <hamon/functional/detail/is_reference_wrapper.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/is_base_of.hpp>
#include <hamon/type_traits/detail/member_object_pointer_traits.hpp>
#include <hamon/type_traits/detail/member_function_pointer_traits.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '...' から '...' への変換です。データが失われる可能性があります。

namespace hamon
{

namespace detail
{

template <typename F>
using member_function_class_type =
	typename hamon::detail::member_function_pointer_traits<F>::class_type;

template <typename F>
using member_object_class_type =
	typename hamon::detail::member_object_pointer_traits<F>::class_type;

// HAMON_INVOKE_RETURN
#define HAMON_INVOKE_RETURN(...) \
    HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)	\
		-> decltype(__VA_ARGS__) \
    { return __VA_ARGS__; }

// invoke_memfun
template <bool IsBaseOf, bool IsRefWrapper>
struct invoke_memfun_impl;

template <bool IsRefWrapper>
struct invoke_memfun_impl<true, IsRefWrapper>
{
	template <typename F, typename A0, typename... Args>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, A0&& t, Args&&... args)
	HAMON_INVOKE_RETURN((std::forward<A0>(t).*f)(std::forward<Args>(args)...))
};

template <>
struct invoke_memfun_impl<false, true>
{
	template <typename F, typename A0, typename... Args>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, A0&& t, Args&&... args)
	HAMON_INVOKE_RETURN((t.get().*f)(std::forward<Args>(args)...))
};

template <>
struct invoke_memfun_impl<false, false>
{
	template <typename F, typename A0, typename... Args>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, A0&& t, Args&&... args)
	HAMON_INVOKE_RETURN(((*std::forward<A0>(t)).*f)(std::forward<Args>(args)...))
};

template <typename ClassT, typename A0>
struct invoke_memfun
	: public invoke_memfun_impl<
		hamon::is_base_of<ClassT, A0>::value,
		hamon::detail::is_reference_wrapper<A0>::value
	>
{};

// invoke_memobj
template <bool IsBaseOf, bool IsRefWrapper>
struct invoke_memobj_impl;

template <bool IsRefWrapper>
struct invoke_memobj_impl<true, IsRefWrapper>
{
	template <typename F, typename A0>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, A0&& t)
	HAMON_INVOKE_RETURN(std::forward<A0>(t).*f)
};

template <>
struct invoke_memobj_impl<false, true>
{
	template <typename F, typename A0>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, A0&& t)
	HAMON_INVOKE_RETURN(t.get().*f)
};

template <>
struct invoke_memobj_impl<false, false>
{
	template <typename F, typename A0>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, A0&& t)
	HAMON_INVOKE_RETURN((*std::forward<A0>(t)).*f)
};

template <typename ClassT, typename A0>
struct invoke_memobj
	: public invoke_memobj_impl<
		hamon::is_base_of<ClassT, A0>::value,
		hamon::detail::is_reference_wrapper<A0>::value
	>
{};

// invoke_other
struct invoke_other
{
	template <typename F, typename... Args>
	static HAMON_CONSTEXPR auto
	invoke(F&& f, Args&&... args)
	HAMON_INVOKE_RETURN(std::forward<F>(f)(std::forward<Args>(args)...))
};

// invoke_impl
template <bool, bool, typename F, typename... Args>
struct invoke_impl;

template <typename F, typename A0, typename... Args>
struct invoke_impl<true, false, F, A0, Args...>
	: public invoke_memfun<member_function_class_type<F>, A0>
{};

template <typename F, typename A0, typename... Args>
struct invoke_impl<false, true, F, A0, Args...>
	: public invoke_memobj<member_object_class_type<F>, A0>
{};

template <typename F, typename... Args>
struct invoke_impl<false, false, F, Args...>
	: public invoke_other
{};

// invoke
template <typename F, typename... Args>
inline HAMON_CONSTEXPR auto
invoke(F&& f, Args&&... args)
HAMON_INVOKE_RETURN((invoke_impl<
		std::is_member_function_pointer<hamon::decay_t<F>>::value,
		std::is_member_object_pointer<hamon::decay_t<F>>::value,
		hamon::decay_t<F>,
		hamon::decay_t<Args>...
	>::invoke(std::forward<F>(f), std::forward<Args>(args)...)))

#undef HAMON_INVOKE_RETURN

}	// namespace detail

}	// namespace hamon

HAMON_WARNING_POP()

#include <utility>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon
{

template <typename F, typename... Args>
inline HAMON_CONSTEXPR auto
invoke(F&& f, Args&&... args)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		detail::invoke(std::forward<F>(f), std::forward<Args>(args)...))

}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // HAMON_FUNCTIONAL_INVOKE_HPP
