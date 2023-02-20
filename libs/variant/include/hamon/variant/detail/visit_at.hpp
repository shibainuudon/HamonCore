/**
 *	@file	visit_at.hpp
 *
 *	@brief	visit_at の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VISIT_AT_HPP
#define HAMON_VARIANT_DETAIL_VISIT_AT_HPP

#include <hamon/variant/detail/access.hpp>
#include <hamon/variant/detail/generic_variant_size.hpp>
#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/invoke_r.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct visit_at
{
private:
	template <typename F, hamon::size_t N>
	struct Vtable;

	template <typename Result, typename Visitor, typename... Variants, hamon::size_t N>
	struct Vtable<Result(*)(Visitor, Variants...), N>
	{
	private:
		using F = Result(*)(Visitor, Variants...);

		template <hamon::size_t I>
		static HAMON_CXX11_CONSTEXPR Result
		invoke_visit(Visitor&& visitor, Variants&&... args)
		{
			return hamon::invoke_r<Result>(
				hamon::forward<Visitor>(visitor),
				variant_detail::access::get<I>(hamon::forward<Variants>(args))...);
		}

		template <hamon::size_t... Is>
		static HAMON_CXX11_CONSTEXPR hamon::array<F, N> const
		get_func_table(hamon::index_sequence<Is...>)
		{
			return { &invoke_visit<Is>... };
		}

	public:
		static HAMON_CXX11_CONSTEXPR F
		get_func(hamon::size_t i)
		{
			return get_func_table(hamon::make_index_sequence<N>{})[i];
		}
	};

public:
	template <typename R = void, typename Visitor, typename... Variants>
	static HAMON_CXX11_CONSTEXPR R
	invoke(hamon::size_t i, Visitor&& visitor, Variants&&... vars)
	{
		using FirstVariant =
			hamon::nth_t<0, hamon::remove_cvref_t<Variants>...>;
		using vtbl_type = Vtable<
			R(*)(Visitor&&, Variants&&...),
			variant_detail::generic_variant_size<FirstVariant>::value>;
		return vtbl_type::get_func(i)(
			hamon::forward<Visitor>(visitor),
			hamon::forward<Variants>(vars)...);
	}
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VISIT_AT_HPP
