/**
 *	@file	range_adaptor.hpp
 *
 *	@brief	range_adaptor の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_RANGE_ADAPTOR_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_RANGE_ADAPTOR_HPP

#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename F>
class range_adaptor
	: public hamon::ranges::range_adaptor_closure<range_adaptor<F>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS F m_f;

public:
	HAMON_CXX11_CONSTEXPR range_adaptor(F f)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<F>::value)
		: m_f(hamon::move(f))
	{}

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::viewable_range_t<R>,
			hamon::invocable_t<F, R>
		>::value>>
	HAMON_CXX14_CONSTEXPR auto operator()(R&& r) &
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		m_f(hamon::forward<R>(r)))

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::viewable_range_t<R>,
			hamon::invocable_t<F, R>
		>::value>>
	HAMON_CXX11_CONSTEXPR auto operator()(R&& r) const&
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		m_f(hamon::forward<R>(r)))

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::viewable_range_t<R>,
			hamon::invocable_t<F, R>
		>::value>>
	HAMON_CXX14_CONSTEXPR auto operator()(R&& r) &&
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::move(m_f)(hamon::forward<R>(r)))

	template <typename R,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::viewable_range_t<R>,
			hamon::invocable_t<F, R>
		>::value>>
	HAMON_CXX11_CONSTEXPR auto operator()(R&& r) const&&
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::move(m_f)(hamon::forward<R>(r)))
};

// deduction guides が使えないときのため
template <typename F>
HAMON_CXX11_CONSTEXPR auto
make_range_adaptor(F&& f)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		range_adaptor<F>(hamon::forward<F>(f)))

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_RANGE_ADAPTOR_HPP
