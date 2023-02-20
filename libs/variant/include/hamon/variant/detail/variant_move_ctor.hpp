/**
 *	@file	variant_move_ctor.hpp
 *
 *	@brief	variant_move_ctor の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_MOVE_CTOR_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_MOVE_CTOR_HPP

#include <hamon/variant/detail/variant_copy_ctor.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

template <bool MoveConstructible, bool TriviallyMoveConstructible, typename... Types>
struct variant_move_ctor_impl;

template <bool Trivial, typename... Types>
struct variant_move_ctor_impl<false, Trivial, Types...> : variant_copy_ctor<Types...>
{
	using variant_copy_ctor<Types...>::variant_copy_ctor;

	// [variant.ctor]/10
	// Constraints: is_move_constructible_v<Ti> is true for all i.
	variant_move_ctor_impl(variant_move_ctor_impl &&) = delete;

	variant_move_ctor_impl()                                         = default;
	variant_move_ctor_impl(variant_move_ctor_impl const&)            = default;
	variant_move_ctor_impl& operator=(variant_move_ctor_impl &&)     = default;
	variant_move_ctor_impl& operator=(variant_move_ctor_impl const&) = default;
};

template <typename... Types>
struct variant_move_ctor_impl<true, true, Types...> : variant_copy_ctor<Types...>
{
	using variant_copy_ctor<Types...>::variant_copy_ctor;

	// [variant.ctor]/13
	// If is_trivially_move_constructible_v<Ti> is true for all i, this constructor is trivial.
	variant_move_ctor_impl(variant_move_ctor_impl &&) = default;

	variant_move_ctor_impl()                                         = default;
	variant_move_ctor_impl(variant_move_ctor_impl const&)            = default;
	variant_move_ctor_impl& operator=(variant_move_ctor_impl &&)     = default;
	variant_move_ctor_impl& operator=(variant_move_ctor_impl const&) = default;
};

template <typename... Types>
struct variant_move_ctor_impl<true, false, Types...> : variant_copy_ctor<Types...>
{
	using variant_copy_ctor<Types...>::variant_copy_ctor;

	HAMON_CXX14_CONSTEXPR
	variant_move_ctor_impl(variant_move_ctor_impl && w)
		// [variant.ctor]/13
		// The exception specification is equivalent to the logical AND of
		// is_nothrow_move_constructible_v<Ti> for all i.
		HAMON_NOEXCEPT_IF((hamon::conjunction<hamon::is_nothrow_move_constructible<Types>...>::value))
	{
		// [variant.ctor]/11
		// If w holds a value, initializes the variant to hold the same alternative as w and
		// direct-initializes the contained value with get<j>(hamon::move(w)), where j is w.index().
		// Otherwise, initializes the variant to not hold a value.

		this->index(w.index());
		if (!w.valueless_by_exception())
		{
			variant_detail::visit_at::invoke(
				this->index(), ctor_visitor{}, *this, hamon::move(w));
		}
	}

	variant_move_ctor_impl()                                         = default;
	variant_move_ctor_impl(variant_move_ctor_impl const&)            = default;
	variant_move_ctor_impl& operator=(variant_move_ctor_impl &&)     = default;
	variant_move_ctor_impl& operator=(variant_move_ctor_impl const&) = default;
};

template <typename... Types>
using variant_move_ctor =
	variant_move_ctor_impl<
		hamon::conjunction<hamon::is_move_constructible<Types>...>::value,
		hamon::conjunction<hamon::is_trivially_move_constructible<Types>...>::value,
		Types...
	>;

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_MOVE_CTOR_HPP
