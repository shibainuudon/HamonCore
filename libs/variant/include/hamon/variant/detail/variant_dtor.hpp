/**
 *	@file	variant_dtor.hpp
 *
 *	@brief	variant_dtor の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_DTOR_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_DTOR_HPP

#include <hamon/variant/detail/variant_base.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct dtor_visitor
{
	template <typename T>
	HAMON_CXX20_CONSTEXPR void operator()(T& v) const
	{
		hamon::destroy_at(hamon::addressof(v));
	}
};

template <bool TriviallyDestructible, typename... Types>
struct variant_dtor_impl;

template <typename... Types>
struct variant_dtor_impl<true, Types...> : variant_base<Types...>
{
	using variant_base<Types...>::variant_base;

	HAMON_CXX14_CONSTEXPR void destroy() HAMON_NOEXCEPT
	{
		this->set_valueless();
	}

	// [variant.dtor]/2
	// If is_trivially_destructible_v<Ti> is true for all Ti, then this destructor is trivial.
	~variant_dtor_impl() = default;

	variant_dtor_impl()                                    = default;
	variant_dtor_impl(variant_dtor_impl const&)            = default;
	variant_dtor_impl(variant_dtor_impl&&)                 = default;
	variant_dtor_impl& operator=(variant_dtor_impl &&)     = default;
	variant_dtor_impl& operator=(variant_dtor_impl const&) = default;
};

template <typename... Types>
struct variant_dtor_impl<false, Types...> : variant_base<Types...>
{
	using variant_base<Types...>::variant_base;

	HAMON_CXX20_CONSTEXPR void destroy() HAMON_NOEXCEPT
	{
		// [variant.dtor]/1
		// If valueless_by_exception() is false, destroys the currently contained value.
		if (!this->valueless_by_exception())
		{
			variant_detail::visit_at::invoke(
				this->index(), dtor_visitor{}, *this);
		}
		this->set_valueless();
	}

	HAMON_CXX20_CONSTEXPR ~variant_dtor_impl() HAMON_NOEXCEPT
	{
		destroy();
	}

	variant_dtor_impl()                                    = default;
	variant_dtor_impl(variant_dtor_impl const&)            = default;
	variant_dtor_impl(variant_dtor_impl&&)                 = default;
	variant_dtor_impl& operator=(variant_dtor_impl &&)     = default;
	variant_dtor_impl& operator=(variant_dtor_impl const&) = default;
};

template <typename... Types>
using variant_dtor =
	variant_dtor_impl<
		hamon::conjunction<hamon::is_trivially_destructible<Types>...>::value,
		Types...
	>;

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_DTOR_HPP
