/**
 *	@file	visit_impl.hpp
 *
 *	@brief	visit_impl の定義
 */

#ifndef HAMON_VARIANT_DETAIL_VISIT_IMPL_HPP
#define HAMON_VARIANT_DETAIL_VISIT_IMPL_HPP

#include <hamon/variant/detail/access.hpp>
#include <hamon/variant/detail/generic_variant_size.hpp>
#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/invoke_r.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_invocable_r.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace variant_detail
{

struct visit_impl
{
private:
	template <bool DeduceResult, typename F, typename IndexSequence, hamon::size_t... Ds>
	struct MultiDimensionVtable;

	// INVOKE を呼び出す特殊化 [variant.visit]/4
	template <typename Result, typename Visitor, typename... Variants, hamon::size_t... Is>
	struct MultiDimensionVtable<true, Result(*)(Visitor, Variants...), hamon::index_sequence<Is...>>
	{
	private:
		using F = Result(*)(Visitor, Variants...);

		static HAMON_CXX11_CONSTEXPR Result
		invoke_impl(Visitor&& visitor, Variants&&... args)
		{
			return hamon::invoke(
				hamon::forward<Visitor>(visitor),
				variant_detail::access::get<Is>(hamon::forward<Variants>(args))...);
		}

		using DeducedResult =
			decltype(hamon::invoke(
				hamon::declval<Visitor>(),
				variant_detail::access::get<Is>(hamon::declval<Variants>())...));

	public:
		static HAMON_CXX11_CONSTEXPR F get_func() { return &invoke_impl; }

		using is_invocable =
			hamon::conjunction<
				hamon::is_invocable<
					Visitor,
					decltype(variant_detail::access::get<Is>(hamon::declval<Variants>()))...
				>,
				hamon::is_same<DeducedResult, Result>
			>;
	};

	// INVOKE<R> を呼び出す特殊化 [variant.visit]/4
	template <typename Result, typename Visitor, typename... Variants, hamon::size_t... Is>
	struct MultiDimensionVtable<false, Result(*)(Visitor, Variants...), hamon::index_sequence<Is...>>
	{
	private:
		using F = Result(*)(Visitor, Variants...);

		static HAMON_CXX11_CONSTEXPR Result
		invoke_impl(Visitor&& visitor, Variants&&... args)
		{
			return hamon::invoke_r<Result>(
				hamon::forward<Visitor>(visitor),
				variant_detail::access::get<Is>(hamon::forward<Variants>(args))...);
		}

	public:
		static HAMON_CXX11_CONSTEXPR F get_func() { return &invoke_impl; }

		using is_invocable =
			hamon::is_invocable_r<
				Result,
				Visitor,
				decltype(variant_detail::access::get<Is>(hamon::declval<Variants>()))...
			>;
	};

	template <bool DeduceResult, typename F, hamon::size_t... Is, hamon::size_t D, hamon::size_t... Rest>
	struct MultiDimensionVtable<DeduceResult, F, hamon::index_sequence<Is...>, D, Rest...>
	{
	private:
		template <hamon::size_t... Js, typename... Args>
		static HAMON_CXX11_CONSTEXPR hamon::array<F, sizeof...(Js)> const
		get_func_impl(hamon::index_sequence<Js...>, Args... rest)
		{
			return
			{
				MultiDimensionVtable<
					DeduceResult, F, hamon::index_sequence<Is..., Js>, Rest...
				>::get_func(rest...)...,
			};
		}

	public:
		template <typename... Args>
		static HAMON_CXX11_CONSTEXPR F get_func(hamon::size_t i, Args... rest)
		{
			return get_func_impl(hamon::make_index_sequence<D>{}, rest...)[i];
		}

	private:
		template <typename IndexSequence>
		struct is_invocable_impl;

		template <hamon::size_t... Js>
		struct is_invocable_impl<hamon::index_sequence<Js...>>
			: hamon::conjunction<
				typename MultiDimensionVtable<
					DeduceResult, F, hamon::index_sequence<Is..., Js>, Rest...
				>::is_invocable...
			>
		{};

	public:
		using is_invocable = is_invocable_impl<hamon::make_index_sequence<D>>;
	};

public:
	template <typename Visitor, typename... Variants>
	using deduced_result_t =
		decltype(hamon::invoke(
			hamon::declval<Visitor>(),
			variant_detail::access::get<0>(hamon::declval<Variants>())...));

private:
	struct Unspecified;

	template <typename R, typename Visitor, typename... Variants>
	struct GenVtable
	{
		using result_type = R;
		using type = MultiDimensionVtable<
			false,
			result_type(*)(Visitor&&, Variants&&...),
			hamon::index_sequence<>,
			variant_detail::generic_variant_size<
				hamon::remove_cvref_t<Variants>
			>::value...
		>;
	};

	template <typename Visitor, typename... Variants>
	struct GenVtable<Unspecified, Visitor, Variants...>
	{
		using result_type = deduced_result_t<Visitor, Variants...>;
		using type = MultiDimensionVtable<
			true,
			result_type(*)(Visitor&&, Variants&&...),
			hamon::index_sequence<>,
			variant_detail::generic_variant_size<
				hamon::remove_cvref_t<Variants>
			>::value...
		>;
	};

public:
	template <typename R = Unspecified, typename Visitor, typename... Variants>
	static HAMON_CXX11_CONSTEXPR typename GenVtable<R, Visitor, Variants...>::result_type
	invoke(Visitor&& visitor, Variants&&... vars)
	{
		using vtbl_type = typename GenVtable<R, Visitor, Variants...>::type;
		return vtbl_type::get_func(vars.index()...)(
			hamon::forward<Visitor>(visitor),
			hamon::forward<Variants>(vars)...);
	}

	template <typename Visitor, typename... Variants>
	using is_invocable =
		typename GenVtable<Unspecified, Visitor, Variants...>::type::is_invocable;

	template <typename R, typename Visitor, typename... Variants>
	using is_invocable_r =
		typename GenVtable<R, Visitor, Variants...>::type::is_invocable;
};

}	// namespace variant_detail

}	// namespace hamon

#endif // HAMON_VARIANT_DETAIL_VISIT_IMPL_HPP
