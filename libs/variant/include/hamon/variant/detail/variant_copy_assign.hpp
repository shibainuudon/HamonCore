/**
 *	@file	variant_copy_assign.hpp
 *
 *	@brief	variant_copy_assign の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_COPY_ASSIGN_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_COPY_ASSIGN_HPP

#include <hamon/variant/detail/variant_assign_t.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct assign_visitor
{
	template <typename T, typename U>
	HAMON_CXX14_CONSTEXPR void operator()(T& v1, U&& v2) const
	{
		v1 = hamon::forward<U>(v2);
	}
};

template <bool CopyAssignable, bool TriviallyCopyAssignable, typename... Types>
struct variant_copy_assign_impl;

template <bool Trivial, typename... Types>
struct variant_copy_assign_impl<false, Trivial, Types...> : variant_assign_t<Types...>
{
	using variant_assign_t<Types...>::variant_assign_t;

	variant_copy_assign_impl& operator=(variant_copy_assign_impl const&) = delete;

	variant_copy_assign_impl()                                       = default;
	variant_copy_assign_impl(variant_copy_assign_impl const&)        = default;
	variant_copy_assign_impl(variant_copy_assign_impl &&)            = default;
	variant_copy_assign_impl& operator=(variant_copy_assign_impl &&) = default;
};

template <typename... Types>
struct variant_copy_assign_impl<true, true, Types...> : variant_assign_t<Types...>
{
	using variant_assign_t<Types...>::variant_assign_t;

	variant_copy_assign_impl& operator=(variant_copy_assign_impl const&) = default;

	variant_copy_assign_impl()                                       = default;
	variant_copy_assign_impl(variant_copy_assign_impl const&)        = default;
	variant_copy_assign_impl(variant_copy_assign_impl &&)            = default;
	variant_copy_assign_impl& operator=(variant_copy_assign_impl &&) = default;
};

template <typename... Types>
struct variant_copy_assign_impl<true, false, Types...> : variant_assign_t<Types...>
{
	using this_type = variant_copy_assign_impl<true, false, Types...>;

	using variant_assign_t<Types...>::variant_assign_t;

	HAMON_CXX14_CONSTEXPR variant_copy_assign_impl&
	operator=(variant_copy_assign_impl const& rhs)
		HAMON_NOEXCEPT_IF((hamon::conjunction<
			hamon::is_nothrow_copy_constructible<Types>...,
			hamon::is_nothrow_copy_assignable<Types>...
		>::value))
	{
		// [variant.assign]/1
		// Let j be rhs.index()

		if (this->valueless_by_exception() && rhs.valueless_by_exception())
		{
			// [variant.assign]/2.1
			// If neither *this nor rhs holds a value, there is no effect.
		}
		else if (rhs.valueless_by_exception())
		{
			// [variant.assign]/2.2
			// Otherwise, if *this holds a value but rhs does not,
			// destroys the value contained in *this and sets *this to not hold a value.
			this->destroy();
		}
		else
		{
			if (this->index() == rhs.index())
			{
				// [variant.assign]/2.3
				// Otherwise, if index() == j, assigns the value contained in rhs
				// to the value contained in *this.
				variant_detail::visit_at::invoke(
					this->index(), assign_visitor{}, *this, rhs);
			}
			else
			{
				// [variant.assign]/2.4
				// Otherwise, if either is_nothrow_copy_constructible_v<Tj> is true or
				// is_nothrow_move_constructible_v<Tj> is false, equivalent to emplace<j>(get<j>(rhs)).
				
				// [variant.assign]/2.5
				// Otherwise, equivalent to operator=(variant(rhs)).
				
				variant_detail::visit_at::invoke(
					rhs.index(), assign_or_emplace_visitor<this_type>{this, rhs.index()}, *this, rhs);
			}
		}

		// [variant.assign]/3
		// Postconditions: index() == rhs.index().

		// [variant.assign]/4
		return *this;
	}

	variant_copy_assign_impl()                                       = default;
	variant_copy_assign_impl(variant_copy_assign_impl const&)        = default;
	variant_copy_assign_impl(variant_copy_assign_impl &&)            = default;
	variant_copy_assign_impl& operator=(variant_copy_assign_impl &&) = default;
};

// [variant.assign]/5
template <typename... Types>
using variant_copy_assign =
	variant_copy_assign_impl<
		hamon::conjunction<
			hamon::is_copy_constructible<Types>...,
			hamon::is_copy_assignable<Types>...
		>::value,
		hamon::conjunction<
			hamon::is_trivially_copy_constructible<Types>...,
			hamon::is_trivially_copy_assignable<Types>...,
			hamon::is_trivially_destructible<Types>...
		>::value,
		Types...
	>;

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_COPY_ASSIGN_HPP
