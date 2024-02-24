/**
 *	@file	tuple_transform.hpp
 *
 *	@brief	tuple_transform の定義
 */

#ifndef HAMON_RANGES_DETAIL_TUPLE_TRANSFORM_HPP
#define HAMON_RANGES_DETAIL_TUPLE_TRANSFORM_HPP

#include <hamon/functional/invoke.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename F>
struct tuple_transform_fn
{
	F& m_f;

	template <typename... Ts>
	HAMON_CXX11_CONSTEXPR auto operator()(Ts&&... elements) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::tuple<hamon::invoke_result_t<F&, Ts>...>(
			hamon::invoke(m_f, hamon::forward<Ts>(elements))...))
};

template <typename F, typename Tuple>
HAMON_CXX11_CONSTEXPR auto tuple_transform(F&& f, Tuple&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::apply(tuple_transform_fn<F>{f}, hamon::forward<Tuple>(t)))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_TUPLE_TRANSFORM_HPP
