/**
 *	@file	variant_move_assign.hpp
 *
 *	@brief	variant_move_assign の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_MOVE_ASSIGN_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_MOVE_ASSIGN_HPP

#include <hamon/variant/detail/variant_copy_assign.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

template <bool MoveAssignable, bool TriviallyMoveAssignable, typename... Types>
struct variant_move_assign_impl;

template <bool Trivial, typename... Types>
struct variant_move_assign_impl<false, Trivial, Types...> : variant_copy_assign<Types...>
{
	using variant_copy_assign<Types...>::variant_copy_assign;

	variant_move_assign_impl& operator=(variant_move_assign_impl &&)     = delete;

	variant_move_assign_impl()                                           = default;
	variant_move_assign_impl(variant_move_assign_impl &&)                = default;
	variant_move_assign_impl(variant_move_assign_impl const&)            = default;
	variant_move_assign_impl& operator=(variant_move_assign_impl const&) = default;
};

template <typename... Types>
struct variant_move_assign_impl<true, true, Types...> : variant_copy_assign<Types...>
{
	using variant_copy_assign<Types...>::variant_copy_assign;

	variant_move_assign_impl& operator=(variant_move_assign_impl &&)     = default;

	variant_move_assign_impl()                                           = default;
	variant_move_assign_impl(variant_move_assign_impl &&)                = default;
	variant_move_assign_impl(variant_move_assign_impl const&)            = default;
	variant_move_assign_impl& operator=(variant_move_assign_impl const&) = default;
};

template <typename... Types>
struct variant_move_assign_impl<true, false, Types...> : variant_copy_assign<Types...>
{
	using this_type = variant_move_assign_impl<true, false, Types...>;

	using variant_copy_assign<Types...>::variant_copy_assign;

	HAMON_CXX14_CONSTEXPR variant_move_assign_impl&
	operator=(variant_move_assign_impl && rhs)
		// [variant.assign]/10
		HAMON_NOEXCEPT_IF((hamon::conjunction<
			hamon::is_nothrow_move_constructible<Types>...,
			hamon::is_nothrow_move_assignable<Types>...
		>::value))
	{
		// [variant.assign]/6
		// Let j be rhs.index()

		if (this->valueless_by_exception() && rhs.valueless_by_exception())
		{
			// [variant.assign]/8.1
			// If neither *this nor rhs holds a value, there is no effect.
		}
		else if (rhs.valueless_by_exception())
		{
			// [variant.assign]/8.2
			// Otherwise, if *this holds a value but rhs does not,
			// destroys the value contained in *this and sets *this to not hold a value.
			this->destroy();
		}
		else
		{
			if (this->index() == rhs.index())
			{
				// [variant.assign]/8.3
				// Otherwise, if index() == j, assigns get<j>(std::move(rhs))
				// to the value contained in *this.
				variant_detail::visit_at::invoke(
					this->index(), assign_visitor{}, *this, hamon::move(rhs));
			}
			else
			{
				// [variant.assign]/8.4
				// Otherwise, equivalent to emplace<j>(get<j>(std::move(rhs))).
				variant_detail::visit_at::invoke(
					rhs.index(), emplace_visitor<this_type>{this, rhs.index()}, *this, hamon::move(rhs));
			}
		}

		// [variant.assign]/10.1
		// If an exception is thrown during the call to Tj's move construction
		// (with j being rhs.index()), the variant will hold no value.

		// [variant.assign]/10.2
		// If an exception is thrown during the call to Tj's move assignment,
		// the state of the contained value is as defined by the exception safety
		// guarantee of Tj's move assignment; index() will be j.

		// [variant.assign]/9
		return *this;
	}

	variant_move_assign_impl()                                           = default;
	variant_move_assign_impl(variant_move_assign_impl &&)                = default;
	variant_move_assign_impl(variant_move_assign_impl const&)            = default;
	variant_move_assign_impl& operator=(variant_move_assign_impl const&) = default;
};

template <typename... Types>
using variant_move_assign =
	variant_move_assign_impl<
		// [variant.assign]/7
		hamon::conjunction<
			hamon::is_move_constructible<Types>...,
			hamon::is_move_assignable<Types>...
		>::value,
		// [variant.assign]/10
		hamon::conjunction<
			hamon::is_trivially_move_constructible<Types>...,
			hamon::is_trivially_move_assignable<Types>...,
			hamon::is_trivially_destructible<Types>...
		>::value,
		Types...
	>;

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_MOVE_ASSIGN_HPP
