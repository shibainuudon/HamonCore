/**
 *	@file	variant_copy_ctor.hpp
 *
 *	@brief	variant_copy_ctor の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VARIANT_COPY_CTOR_HPP
#define HAMON_VARIANT_DETAIL_VARIANT_COPY_CTOR_HPP

#include <hamon/variant/detail/variant_dtor.hpp>
#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct ctor_visitor
{
	template <typename T, typename... Args>
	HAMON_CXX14_CONSTEXPR auto operator()(T& v1, Args&&... args) const
	->decltype(hamon::construct_at(hamon::addressof(v1), hamon::forward<Args>(args)...))
	{
		return hamon::construct_at(hamon::addressof(v1), hamon::forward<Args>(args)...);
	}
};

template <bool CopyConstructible, bool TriviallyCopyConstructible, typename... Types>
struct variant_copy_ctor_impl;

template <bool Trivial, typename... Types>
struct variant_copy_ctor_impl<false, Trivial, Types...> : variant_dtor<Types...>
{
	using variant_dtor<Types...>::variant_dtor;

	// [variant.ctor]/9
	// This constructor is defined as deleted unless is_copy_constructible_v<Ti> is true for all i.
	variant_copy_ctor_impl(variant_copy_ctor_impl const&) = delete;

	variant_copy_ctor_impl()                                         = default;
	variant_copy_ctor_impl(variant_copy_ctor_impl&&)                 = default;
	variant_copy_ctor_impl& operator=(variant_copy_ctor_impl &&)     = default;
	variant_copy_ctor_impl& operator=(variant_copy_ctor_impl const&) = default;
};

template <typename... Types>
struct variant_copy_ctor_impl<true, true, Types...> : variant_dtor<Types...>
{
	using variant_dtor<Types...>::variant_dtor;

	// [variant.ctor]/9
	// If is_trivially_copy_constructible_v<Ti> is true for all i, this constructor is trivial.
	variant_copy_ctor_impl(variant_copy_ctor_impl const&) = default;

	variant_copy_ctor_impl()                                         = default;
	variant_copy_ctor_impl(variant_copy_ctor_impl&&)                 = default;
	variant_copy_ctor_impl& operator=(variant_copy_ctor_impl &&)     = default;
	variant_copy_ctor_impl& operator=(variant_copy_ctor_impl const&) = default;
};

template <typename... Types>
struct variant_copy_ctor_impl<true, false, Types...> : variant_dtor<Types...>
{
	using base_type = variant_dtor<Types...>;
	using base_type::base_type;

	HAMON_CXX14_CONSTEXPR variant_copy_ctor_impl(variant_copy_ctor_impl const& w)
	HAMON_NOEXCEPT_IF((
		hamon::conjunction<hamon::is_nothrow_copy_constructible<Types>...>::value))	// extension
		: base_type()
	{
		// [variant.ctor]/7
		// If w holds a value, initializes the variant to hold the same alternative as w and
		// direct-initializes the contained value with get<j>(w), where j is w.index().
		// Otherwise, initializes the variant to not hold a value.
		this->index(w.index());
		if (!w.valueless_by_exception())
		{
			variant_detail::visit_at::invoke(
				this->index(), ctor_visitor{}, *this, w);
		}
	}

	variant_copy_ctor_impl()                                         = default;
	variant_copy_ctor_impl(variant_copy_ctor_impl&&)                 = default;
	variant_copy_ctor_impl& operator=(variant_copy_ctor_impl &&)     = default;
	variant_copy_ctor_impl& operator=(variant_copy_ctor_impl const&) = default;
};

template <typename... Types>
using variant_copy_ctor =
	variant_copy_ctor_impl<
		hamon::conjunction<hamon::is_copy_constructible<Types>...>::value,
		hamon::conjunction<hamon::is_trivially_copy_constructible<Types>...>::value,
		Types...
	>;

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VARIANT_COPY_CTOR_HPP
