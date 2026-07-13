/**
 *	@file	data.hpp
 *
 *	@brief	ranges::data の定義
 */

#ifndef HAMON_RANGES_ACCESS_DATA_HPP
#define HAMON_RANGES_ACCESS_DATA_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::data;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/detail/has_member_data.hpp>
#include <hamon/ranges/detail/begin_data.hpp>
#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.14 ranges::data[range.prim.data]
struct data_fn
{
private:
	// [range.prim.data]/2.3
	template <HAMON_CONSTRAINED_PARAM(has_member_data, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			HAMON_AUTO_CAST(t.data()))

	// [range.prim.data]/2.4
	template <HAMON_CONSTRAINED_PARAM(begin_data, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::to_address(ranges::begin(t)))

	// [range.prim.data]/2.5
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.prim.data]/2.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<2>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.prim.data]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::data_fn data{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_DATA_HPP
