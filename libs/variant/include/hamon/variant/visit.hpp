/**
 *	@file	visit.hpp
 *
 *	@brief	visit の定義
 */

#ifndef HAMON_VARIANT_VISIT_HPP
#define HAMON_VARIANT_VISIT_HPP

#include <hamon/variant/config.hpp>

#if defined(HAMON_USE_STD_VARIANT)

namespace hamon
{

using std::visit;

}	// namespace hamon

#else

#include <hamon/variant/detail/visit_impl.hpp>
#include <hamon/variant/variant_fwd.hpp>
#include <hamon/variant/bad_variant_access.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

// [variant.visit]/1
template <typename... Types>
inline HAMON_CXX11_CONSTEXPR variant<Types...>&
as_variant(variant<Types...> & var) HAMON_NOEXCEPT { return var; }

template <typename... Types>
inline HAMON_CXX11_CONSTEXPR variant<Types...> const&
as_variant(variant<Types...> const& var) HAMON_NOEXCEPT { return var; }

template <typename... Types>
inline HAMON_CXX11_CONSTEXPR variant<Types...>&&
as_variant(variant<Types...> && var) HAMON_NOEXCEPT { return hamon::move(var); }

template <typename... Types>
inline HAMON_CXX11_CONSTEXPR variant<Types...> const&&
as_variant(variant<Types...> const&& var) HAMON_NOEXCEPT { return hamon::move(var); }

inline HAMON_CXX11_CONSTEXPR bool
any_valueless() HAMON_NOEXCEPT
{
	return false;
}

template <typename Variant0, typename... Variants>
inline HAMON_CXX11_CONSTEXPR bool
any_valueless(Variant0&& var0, Variants&&... vars) HAMON_NOEXCEPT
{
	return
		variant_detail::as_variant(var0).valueless_by_exception() ||
		any_valueless(hamon::forward<Variants>(vars)...);
}

template <typename... Variants>
inline HAMON_CXX11_CONSTEXPR int
throw_if_valueless(Variants&&... vars)
{
	// [variant.visit]/7
	return any_valueless(hamon::forward<Variants>(vars)...) ?
		(hamon::throw_bad_variant_access(), 0) : 0;
}

}	// namespace variant_detail

// [variant.visit] visitation
template <
	typename Visitor,
	typename... Variants,
	// [variant.visit]/2
	typename = hamon::void_t<decltype(variant_detail::as_variant(hamon::declval<Variants>()))...>,
	typename R = variant_detail::visit_impl::deduced_result_t<Visitor, Variants...>,
	// [variant.visit]/5
	typename = hamon::enable_if_t<
		variant_detail::visit_impl::is_invocable<Visitor, Variants...>::value
	>
>
inline HAMON_CXX11_CONSTEXPR R
visit(Visitor&& vis, Variants&&... vars)
{
	return
		// [variant.visit]/7
		variant_detail::throw_if_valueless(hamon::forward<Variants>(vars)...),
		variant_detail::visit_impl::invoke(
			hamon::forward<Visitor>(vis),
			variant_detail::as_variant(hamon::forward<Variants>(vars))...);
}

template <
	typename R,
	typename Visitor,
	typename... Variants,
	// [variant.visit]/2
	typename = hamon::void_t<decltype(variant_detail::as_variant(hamon::declval<Variants>()))...>,
	// [variant.visit]/5
	typename = hamon::enable_if_t<
		variant_detail::visit_impl::is_invocable_r<R, Visitor, Variants...>::value
	>
>
inline HAMON_CXX11_CONSTEXPR R
visit(Visitor&& vis, Variants&&... vars)
{
	return
		// [variant.visit]/7
		variant_detail::throw_if_valueless(hamon::forward<Variants>(vars)...),
		variant_detail::visit_impl::invoke<R>(
			hamon::forward<Visitor>(vis),
			variant_detail::as_variant(hamon::forward<Variants>(vars))...);
}

}	// namespace hamon

#endif

#endif // HAMON_VARIANT_VISIT_HPP
