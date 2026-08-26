/**
 *	@file	rend.hpp
 *
 *	@brief	ranges::rend の定義
 */

#ifndef HAMON_RANGES_ACCESS_REND_HPP
#define HAMON_RANGES_ACCESS_REND_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/detail/has_member_rend.hpp>
#include <hamon/ranges/detail/has_adl_rend.hpp>
#include <hamon/ranges/detail/reversable.hpp>
#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.7 ranges::rend[range.access.rend]

struct rend_fn
{
private:
	// [range.access.rend]/2.3
	template <HAMON_CONSTRAINT(has_member_rend, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(t.rend()))

	// [range.access.rend]/2.4
	template <HAMON_CONSTRAINT(has_adl_rend, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(rend(t)))

	// [range.access.rend]/2.5
	template <HAMON_CONSTRAINT(reversable, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(ranges::begin(t))
	->decltype(hamon::make_reverse_iterator(ranges::begin(t)))
	{
		return hamon::make_reverse_iterator(ranges::begin(t));
	}

	// [range.access.rend]/2.6
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.access.rend]/2.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<3>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.rend]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::rend_fn rend{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ACCESS_REND_HPP
