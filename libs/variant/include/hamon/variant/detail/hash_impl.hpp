/**
 *	@file	hash_impl.hpp
 *
 *	@brief	hash_impl の定義
 */

#ifndef HAMON_VARIANT_DETAIL_HASH_IMPL_HPP
#define HAMON_VARIANT_DETAIL_HASH_IMPL_HPP

#include <hamon/variant/detail/visit_at.hpp>
#include <hamon/concepts/detail/cpp17_hash.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/detail/disabled_hash.hpp>
#include <hamon/functional/ranges/hash_combine.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <functional>	// std::hash

namespace hamon
{

namespace variant_detail
{

struct hash_visitor
{
	template <typename T>
	hamon::size_t operator()(T const& v) const
	{
		return std::hash<T>{}(v);
	}
};

template <typename Variant, typename = void>
struct hash_impl : public hamon::detail::disabled_hash
{};

template <typename... Types>
struct hash_impl<hamon::variant<Types...>,
	hamon::enable_if_t<hamon::conjunction<
		hamon::detail::cpp17_hash_t<
			std::hash<hamon::remove_const_t<Types>>, hamon::remove_const_t<Types>
		>...
	>::value>
>
{
	HAMON_NODISCARD hamon::size_t
	operator()(hamon::variant<Types...> const& var) const
	{
		if (var.valueless_by_exception())
		{
			return 0xaa7ac8cd;
		}

		return hamon::ranges::hash_combine(
			variant_detail::visit_at::invoke<hamon::size_t>(
				var.index(), hash_visitor{}, var),
			var.index()
		);
	}
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_HASH_IMPL_HPP
