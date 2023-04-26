/**
 *	@file	uses_allocator_construction_type.hpp
 *
 *	@brief	uses_allocator_construction_type を定義
 */

#ifndef HAMON_MEMORY_DETAIL_USES_ALLOCATOR_CONSTRUCTION_TYPE_HPP
#define HAMON_MEMORY_DETAIL_USES_ALLOCATOR_CONSTRUCTION_TYPE_HPP

#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>
#include <memory>	// uses_allocator

namespace hamon
{

namespace detail
{

// Uses-allocator construction
// [allocator.uses.construction]/2 の仕様に従って、
// uses-allocator構築のための引数の渡し方の種類を取得する。
struct uses_allocator_construction_type
{
	// Allocator を使わない
	struct NoAlloc{};

	// allocator_arg_t, Allocator を最初に渡す
	struct FirstAlloc{};

	// Allocator を最後に渡す
	struct LastAlloc{};

	// uses-allocator 構築できない
	struct Invalid{};

	template <typename T, typename Alloc, typename... Args>
	using type =
		hamon::conditional_t<
			!std::uses_allocator<hamon::remove_cv_t<T>, Alloc>::value,
			hamon::conditional_t<
				hamon::is_constructible<T, Args...>::value,
				NoAlloc,		// [allocator.uses.construction]/2.1
				Invalid
			>,
			hamon::conditional_t<
				hamon::is_constructible<T, hamon::allocator_arg_t, Alloc const&, Args...>::value,
				FirstAlloc,		// [allocator.uses.construction]/2.2
				hamon::conditional_t<
					hamon::is_constructible<T, Args..., Alloc const&>::value,
					LastAlloc,	// [allocator.uses.construction]/2.3
					Invalid
				>
			>
		>;
};

template <typename T, typename Alloc, typename... Args>
using uses_allocator_construction_type_t =
	typename uses_allocator_construction_type::template type<T, Alloc, Args...>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_USES_ALLOCATOR_CONSTRUCTION_TYPE_HPP
