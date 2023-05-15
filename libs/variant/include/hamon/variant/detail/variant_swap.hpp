/**
 *	@file	variant_swap.hpp
 *
 *	@brief	variant_swap の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_SWAP_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_SWAP_HPP

#include <hamon/variant/detail/variant_move_assign.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/adl_swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct swap_visitor
{
	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T& v1, T& v2) const
	{
		hamon::adl_swap(v1, v2);
	}
};

template <typename... Types>
struct variant_swap : public variant_move_assign<Types...>
{
	using variant_move_assign<Types...>::variant_move_assign;

	variant_swap()                               = default;
	variant_swap(variant_swap &&)                = default;
	variant_swap(variant_swap const&)            = default;
	variant_swap& operator=(variant_swap &&)     = default;
	variant_swap& operator=(variant_swap const&) = default;

	HAMON_CXX14_CONSTEXPR void swap(variant_swap& rhs)
	{
		if (this->valueless_by_exception() && rhs.valueless_by_exception())
		{
			// [variant.swap]/3.1
			// no effect
		}
		else if (this->index() == rhs.index())
		{
			// [variant.swap]/3.2
			// calls swap(get<i>(*this), get<i>(rhs))
			variant_detail::visit_at::invoke(
				this->index(), variant_detail::swap_visitor{}, *this, rhs);
		}
		else
		{
			// [variant.swap]/3.3
			// exchanges values of rhs and *this
			auto tmp = hamon::move(*this);
			*this = hamon::move(rhs);
			rhs = hamon::move(tmp);
		}
	}
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_SWAP_HPP
