/**
 *	@file	bind_front.hpp
 *
 *	@brief	bind_front クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_BIND_FRONT_HPP
#define HAMON_FUNCTIONAL_BIND_FRONT_HPP

#include <hamon/functional/config.hpp>

#if defined(__cpp_lib_bind_front) && (__cpp_lib_bind_front >= 202306L)	// P2714R1

#define HAMON_USE_STD_BIND_FRONT

namespace hamon
{

using std::bind_front;

}	// namespace hamon

#else

#include <hamon/functional/invoke.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_member_pointer.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence_for.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct bind_front_ctor_tag{};

template <typename FD, typename... BoundArgs>
struct bind_front_impl
{
private:
	HAMON_NO_UNIQUE_ADDRESS FD m_fd;
	HAMON_NO_UNIQUE_ADDRESS hamon::tuple<BoundArgs...> m_bound_args;

	using BoundIndices = hamon::index_sequence_for<BoundArgs...>;

	template <typename FD2, typename BoundArgs2, size_t... Is, typename... Args>
	static HAMON_CXX11_CONSTEXPR auto
	Invoke(FD2&& fd, BoundArgs2&& bound_args, hamon::index_sequence<Is...>, Args&&... call_args)
		// [func.bind.partial]/4.1
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::invoke(
				hamon::forward<FD2>(fd),
				hamon::get<Is>(hamon::forward<BoundArgs2>(bound_args))...,
				hamon::forward<Args>(call_args)...))

public:
	template <typename F, typename... Args>
	explicit HAMON_CXX11_CONSTEXPR
	bind_front_impl(bind_front_ctor_tag, F&& f, Args&&... args)
		// [func.bind.partial]/5
		HAMON_NOEXCEPT_IF(
			hamon::conjunction<
				hamon::is_nothrow_constructible<FD, F>,
				hamon::is_nothrow_constructible<BoundArgs, Args>...
			>::value)
		: m_fd(hamon::forward<F>(f))
		, m_bound_args(hamon::forward<Args>(args)...)
	{
		static_assert(sizeof...(Args) == sizeof...(BoundArgs), "");
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Args&&... call_args) &
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		Invoke(m_fd, m_bound_args, BoundIndices(), hamon::forward<Args>(call_args)...))

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR auto
	operator()(Args&&... call_args) const &
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		Invoke(m_fd, m_bound_args, BoundIndices(), hamon::forward<Args>(call_args)...))

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Args&&... call_args) &&
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		Invoke(hamon::move(m_fd), hamon::move(m_bound_args), BoundIndices(), hamon::forward<Args>(call_args)...))

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR auto
	operator()(Args&&... call_args) const &&
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		Invoke(hamon::move(m_fd), hamon::move(m_bound_args), BoundIndices(), hamon::forward<Args>(call_args)...))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

template <typename F, typename... Args>
using bind_front_t = bind_front_impl<hamon::decay_t<F>, hamon::decay_t<Args>...>;

}	// namespace detail

// 22.10.14 Function templates bind_front and bind_back	[func.bind.partial]

template <typename F, typename... Args>
HAMON_CXX11_CONSTEXPR hamon::detail::bind_front_t<F, Args...>
bind_front(F&& f, Args&&... args)
	HAMON_NOEXCEPT_IF_EXPR(
		hamon::detail::bind_front_t<F, Args...>(
			hamon::detail::bind_front_ctor_tag{},
			hamon::forward<F>(f),
			hamon::forward<Args>(args)...))
{
	// [func.bind.partial]/1.2
	using FD = hamon::decay_t<F>;

	// [func.bind.partial]/2
	static_assert(hamon::is_constructible<FD, F>::value, "");
	static_assert(hamon::is_move_constructible<FD>::value, "");
	static_assert(hamon::conjunction<hamon::is_constructible<hamon::decay_t<Args>, Args>...>::value, "");
	static_assert(hamon::conjunction<hamon::is_move_constructible<hamon::decay_t<Args>>...>::value, "");

	return hamon::detail::bind_front_t<F, Args...>(
		hamon::detail::bind_front_ctor_tag{},
		hamon::forward<F>(f),
		hamon::forward<Args>(args)...);
}

#if defined(HAMON_HAS_CXX17_NONTYPE_TEMPLATE_PARAMETER_AUTO)

template <auto f, typename... Args>
HAMON_CXX11_CONSTEXPR hamon::detail::bind_front_t<decltype(f), Args...>
bind_front(Args&&... args)
	HAMON_NOEXCEPT_IF_EXPR(
		hamon::detail::bind_front_t<decltype(f), Args...>(
			hamon::detail::bind_front_ctor_tag{},
			f,
			hamon::forward<Args>(args)...))
{
	// [func.bind.partial]/6.1
	using F = decltype(f);

	// [func.bind.partial]/7.1
	static_assert(hamon::conjunction<hamon::is_constructible<hamon::decay_t<Args>, Args>...>::value, "");
	// [func.bind.partial]/7.2
	static_assert(hamon::conjunction<hamon::is_move_constructible<hamon::decay_t<Args>>...>::value, "");
	// [func.bind.partial]/7.3
	if constexpr (hamon::is_pointer<F>::value || hamon::is_member_pointer<F>::value)
	{
		static_assert(f != nullptr);
	}

	return hamon::detail::bind_front_t<F, Args...>(
		hamon::detail::bind_front_ctor_tag{},
		f,
		hamon::forward<Args>(args)...);
}

#endif

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_BIND_FRONT_HPP
