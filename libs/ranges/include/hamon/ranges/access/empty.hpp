/**
 *	@file	empty.hpp
 *
 *	@brief	ranges::empty の定義
 */

#ifndef HAMON_RANGES_ACCESS_EMPTY_HPP
#define HAMON_RANGES_ACCESS_EMPTY_HPP

#include <hamon/ranges/detail/has_member_empty.hpp>
#include <hamon/ranges/detail/size0_empty.hpp>
#include <hamon/ranges/detail/eq_iter_empty.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.13 ranges::empty[range.prim.empty]
struct empty_fn
{
private:
	// [range.prim.empty]/2.1
	template <typename T, typename = hamon::enable_if_t<
		hamon::is_unbounded_array<hamon::remove_cvref_t<T>>::value>>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<4>) = delete;

	// [range.prim.empty]/2.2
	template <HAMON_CONSTRAINT(has_member_empty, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(bool(t.empty()))

	// [range.prim.empty]/2.3
	template <HAMON_CONSTRAINT(size0_empty, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(ranges::size(t) == 0)

	// [range.prim.empty]/2.4
	template <HAMON_CONSTRAINT(eq_iter_empty, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			bool(ranges::begin(t) == ranges::end(t)))

	// [range.prim.empty]/2.5
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<4>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.prim.empty]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::empty_fn empty{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ACCESS_EMPTY_HPP
