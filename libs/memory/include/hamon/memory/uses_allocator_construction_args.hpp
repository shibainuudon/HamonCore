/**
 *	@file	uses_allocator_construction_args.hpp
 *
 *	@brief	uses_allocator_construction_args の定義
 */

#ifndef HAMON_MEMORY_USES_ALLOCATOR_CONSTRUCTION_ARGS_HPP
#define HAMON_MEMORY_USES_ALLOCATOR_CONSTRUCTION_ARGS_HPP

#include <memory>

#if 0

namespace hamon
{

using std::uses_allocator_construction_args;

}	// namespace hamon

#else

#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/tuple/tuple.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/utility/forward.hpp>

#define HAMON_DECLTYPE_RETURN(...)	\
	-> decltype(__VA_ARGS__)		\
	{ return __VA_ARGS__; }

namespace hamon
{

namespace detail
{

template <typename T>
using is_cv_pair =
	hamon::detail::is_specialization_of_pair<hamon::remove_cv_t<T>>;

// [allocator.uses.construction]/5.1
template <typename T, typename Alloc, typename... Args,
	typename = hamon::enable_if_t<
		!std::uses_allocator<hamon::remove_cv_t<T>, Alloc>::value &&
		hamon::is_constructible<T, Args...>::value>>
constexpr auto
uses_allocator_construction_args_impl(hamon::detail::overload_priority<2>, Alloc const&, Args&&... args) noexcept
HAMON_DECLTYPE_RETURN(
	hamon::forward_as_tuple(hamon::forward<Args>(args)...))

// [allocator.uses.construction]/5.2
template <typename T, typename Alloc, typename... Args,
	typename = hamon::enable_if_t<
		std::uses_allocator<hamon::remove_cv_t<T>, Alloc>::value &&
		hamon::is_constructible<T, hamon::allocator_arg_t, Alloc const&, Args...>::value>>
constexpr auto
uses_allocator_construction_args_impl(hamon::detail::overload_priority<1>, Alloc const& alloc, Args&&... args) noexcept
HAMON_DECLTYPE_RETURN(
	hamon::tuple<hamon::allocator_arg_t, Alloc const&, Args&&...>(
		hamon::allocator_arg, alloc, hamon::forward<Args>(args)...))

// [allocator.uses.construction]/5.3
template <typename T, typename Alloc, typename... Args,
	typename = hamon::enable_if_t<
		std::uses_allocator<hamon::remove_cv_t<T>, Alloc>::value &&
		hamon::is_constructible<T, Args..., Alloc const&>::value>>
constexpr auto
uses_allocator_construction_args_impl(hamon::detail::overload_priority<0>, Alloc const& alloc, Args&&... args) noexcept
HAMON_DECLTYPE_RETURN(
	hamon::forward_as_tuple(hamon::forward<Args>(args)..., alloc))

// [allocator.uses.construction]/5.4

}	// namespace detail

// Uses-allocator construction	[allocator.uses.construction]
template <typename T, typename Alloc, typename... Args,
	typename = hamon::enable_if_t<
		!hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/4
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, Args&&... args) noexcept
HAMON_DECLTYPE_RETURN(
	hamon::detail::uses_allocator_construction_args_impl<T>(
		hamon::detail::overload_priority<2>{},
		alloc, hamon::forward<Args>(args)...))

namespace detail
{

template <typename Alloc, typename T>
struct UsesAllocatorConstructionArgs
{
	Alloc const& m_alloc;

	template <typename... Args>
	constexpr auto operator()(Args&&... args) const noexcept
	HAMON_DECLTYPE_RETURN(
		hamon::uses_allocator_construction_args<T>(
			m_alloc, hamon::forward<Args>(args)...))
};

}	// namespace detail

template <typename T, typename Alloc, typename Tuple1, typename Tuple2,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/7
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, hamon::piecewise_construct_t, Tuple1&& x, Tuple2&& y) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/8
	hamon::make_tuple(
		hamon::piecewise_construct,
		hamon::apply(
			hamon::detail::UsesAllocatorConstructionArgs<Alloc, typename T::first_type>{alloc},
			hamon::forward<Tuple1>(x)),
		hamon::apply(
			hamon::detail::UsesAllocatorConstructionArgs<Alloc, typename T::second_type>{alloc},
			hamon::forward<Tuple2>(y))
	))

template <typename T, typename Alloc,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/9
constexpr auto
uses_allocator_construction_args(Alloc const& alloc) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/10
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::tuple<>{},
		hamon::tuple<>{}))

template <typename T, typename Alloc, typename U, typename V,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/11
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, U&& u, V&& v) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/12
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(hamon::forward<U>(u)),
		hamon::forward_as_tuple(hamon::forward<V>(v))))

template <typename T, typename Alloc, typename U, typename V,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/13
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V>& pr) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/14
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(pr.first),
		hamon::forward_as_tuple(pr.second)))

template <typename T, typename Alloc, typename U, typename V,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/13
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V> const& pr) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/14
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(pr.first),
		hamon::forward_as_tuple(pr.second)))

template <typename T, typename Alloc, typename U, typename V,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/15
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V>&& pr) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/16
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(get<0>(hamon::move(pr))),
		hamon::forward_as_tuple(get<1>(hamon::move(pr)))))

template <typename T, typename Alloc, typename U, typename V,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/15
constexpr auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V> const&& pr) noexcept
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/16
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(get<0>(hamon::move(pr))),
		hamon::forward_as_tuple(get<1>(hamon::move(pr)))))

#if 0	// TODO
template <typename T, typename Alloc, pair-like P>
constexpr auto uses_allocator_construction_args(Alloc const& alloc, P&& p) noexcept;
template <typename T, typename Alloc, typename U>
constexpr auto uses_allocator_construction_args(Alloc const& alloc, U&& u) noexcept;
#endif

}	// namespace hamon

#undef HAMON_DECLTYPE_RETURN

#endif

#endif // HAMON_MEMORY_USES_ALLOCATOR_CONSTRUCTION_ARGS_HPP
