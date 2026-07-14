/**
 *	@file	reserve_hint.hpp
 *
 *	@brief	ranges::reserve_hint の定義
 */

#ifndef HAMON_RANGES_ACCESS_RESERVE_HINT_HPP
#define HAMON_RANGES_ACCESS_RESERVE_HINT_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_reserve_hint) && (__cpp_lib_ranges_reserve_hint >= 202502L)

namespace hamon {
namespace ranges {

using std::ranges::reserve_hint;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/detail/has_member_reserve_hint.hpp>
#include <hamon/ranges/detail/has_adl_reserve_hint.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/utility/forward.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.12 ranges::reserve_hint[range.prim.size.hint]
struct reserve_hint_fn
{
private:
	// [range.prim.size.hint]/2.1
	template <typename T>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			ranges::size(t))

	// [range.prim.size.hint]/2.2
	template <HAMON_CONSTRAINT(has_member_reserve_hint, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			HAMON_AUTO_CAST(t.reserve_hint()))

	// [range.prim.size.hint]/2.3
	template <HAMON_CONSTRAINT(has_adl_reserve_hint, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			HAMON_AUTO_CAST(reserve_hint(t)))

	// [range.prim.size.hint]/2.4
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<3>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.prim.size.hint]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::reserve_hint_fn reserve_hint{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_RESERVE_HINT_HPP
