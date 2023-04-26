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
#include <hamon/memory/detail/uses_allocator_construction_type.hpp>
#include <hamon/concepts/detail/is_specialization_of_pair.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/apply.hpp>
#include <hamon/tuple/forward_as_tuple.hpp>
#include <hamon/tuple/make_tuple.hpp>
#include <hamon/tuple/tuple.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

#define HAMON_DECLTYPE_RETURN(...)	\
	-> decltype(__VA_ARGS__)		\
	{ return __VA_ARGS__; }

namespace hamon
{

namespace detail
{

template <typename T>
struct uses_allocator_construction_args_impl
{
private:
	// [allocator.uses.construction]/5.1
	template <typename Alloc, typename... Args>
	static HAMON_CXX11_CONSTEXPR auto
	impl(uses_allocator_construction_type::NoAlloc, Alloc const&, Args&&... args) HAMON_NOEXCEPT
	HAMON_DECLTYPE_RETURN(
		hamon::forward_as_tuple(hamon::forward<Args>(args)...))

	// [allocator.uses.construction]/5.2
	template <typename Alloc, typename... Args>
	static HAMON_CXX11_CONSTEXPR auto
	impl(uses_allocator_construction_type::FirstAlloc, Alloc const& alloc, Args&&... args) HAMON_NOEXCEPT
	HAMON_DECLTYPE_RETURN(
		hamon::tuple<hamon::allocator_arg_t, Alloc const&, Args&&...>(
			hamon::allocator_arg, alloc, hamon::forward<Args>(args)...))

	// [allocator.uses.construction]/5.3
	template <typename Alloc, typename... Args>
	static HAMON_CXX11_CONSTEXPR auto
	impl(uses_allocator_construction_type::LastAlloc, Alloc const& alloc, Args&&... args) HAMON_NOEXCEPT
	HAMON_DECLTYPE_RETURN(
		hamon::forward_as_tuple(hamon::forward<Args>(args)..., alloc))

	// [allocator.uses.construction]/5.4
	// Otherwise, the program is ill-formed.

public:
	template <typename Alloc, typename... Args>
	static HAMON_CXX11_CONSTEXPR auto
	invoke(Alloc const& alloc, Args&&... args) HAMON_NOEXCEPT
	HAMON_DECLTYPE_RETURN(impl(
		hamon::detail::uses_allocator_construction_type_t<T, Alloc, Args...>{},
		alloc, hamon::forward<Args>(args)...))
};

// is_cv_pair
template <typename T>
using is_cv_pair =
	hamon::detail::is_specialization_of_pair<hamon::remove_cv_t<T>>;

}	// namespace detail

// Uses-allocator construction	[allocator.uses.construction]
template <typename T, typename Alloc, typename... Args,
	typename = hamon::enable_if_t<
		!hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/4
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, Args&&... args) HAMON_NOEXCEPT
HAMON_DECLTYPE_RETURN(
	hamon::detail::uses_allocator_construction_args_impl<T>::invoke(
		alloc, hamon::forward<Args>(args)...))

namespace detail
{

template <typename Alloc, typename T>
struct UsesAllocatorConstructionArgs
{
	Alloc const& m_alloc;

	template <typename... Args>
	HAMON_CXX11_CONSTEXPR auto operator()(Args&&... args) const HAMON_NOEXCEPT
	HAMON_DECLTYPE_RETURN(
		hamon::uses_allocator_construction_args<T>(
			m_alloc, hamon::forward<Args>(args)...))
};

}	// namespace detail

template <typename T, typename Alloc, typename Tuple1, typename Tuple2,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/7
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, hamon::piecewise_construct_t, Tuple1&& x, Tuple2&& y) HAMON_NOEXCEPT
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
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc) HAMON_NOEXCEPT
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
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, U&& u, V&& v) HAMON_NOEXCEPT
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
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V>& pr) HAMON_NOEXCEPT
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
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V> const& pr) HAMON_NOEXCEPT
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
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V>&& pr) HAMON_NOEXCEPT
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/16
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(hamon::adl_get<0>(hamon::move(pr))),
		hamon::forward_as_tuple(hamon::adl_get<1>(hamon::move(pr)))))

template <typename T, typename Alloc, typename U, typename V,
	typename = hamon::enable_if_t<
		hamon::detail::is_cv_pair<T>::value>>		// [allocator.uses.construction]/15
HAMON_CXX11_CONSTEXPR auto
uses_allocator_construction_args(Alloc const& alloc, hamon::pair<U, V> const&& pr) HAMON_NOEXCEPT
HAMON_DECLTYPE_RETURN(
	// [allocator.uses.construction]/16
	hamon::uses_allocator_construction_args<T>(
		alloc,
		hamon::piecewise_construct,
		hamon::forward_as_tuple(hamon::adl_get<0>(hamon::move(pr))),
		hamon::forward_as_tuple(hamon::adl_get<1>(hamon::move(pr)))))

#if 0	// TODO
template <typename T, typename Alloc, pair-like P>
HAMON_CXX11_CONSTEXPR auto uses_allocator_construction_args(Alloc const& alloc, P&& p) HAMON_NOEXCEPT;
template <typename T, typename Alloc, typename U>
HAMON_CXX11_CONSTEXPR auto uses_allocator_construction_args(Alloc const& alloc, U&& u) HAMON_NOEXCEPT;
#endif

}	// namespace hamon

#undef HAMON_DECLTYPE_RETURN

#endif

#endif // HAMON_MEMORY_USES_ALLOCATOR_CONSTRUCTION_ARGS_HPP
