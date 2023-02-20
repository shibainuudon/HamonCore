/**
 *	@file	generic_variant_size.hpp
 *
 *	@brief	generic_variant_size の定義
 */

#ifndef HAMON_VARIANT_DETAIL_GENERIC_VARIANT_SIZE_HPP
#define HAMON_VARIANT_DETAIL_GENERIC_VARIANT_SIZE_HPP

#include <hamon/variant/variant_fwd.hpp>
#include <hamon/variant/detail/variant_base.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace variant_detail
{

template <typename... Types>
hamon::integral_constant<hamon::size_t, sizeof...(Types)>
generic_variant_size_impl(variant_base<Types...> const&);

template <typename... Types>
hamon::integral_constant<hamon::size_t, sizeof...(Types)>
generic_variant_size_impl(variant<Types...> const&);

template <typename Variant>
using generic_variant_size =
	decltype(generic_variant_size_impl(
		hamon::declval<Variant const&>()));

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_GENERIC_VARIANT_SIZE_HPP
