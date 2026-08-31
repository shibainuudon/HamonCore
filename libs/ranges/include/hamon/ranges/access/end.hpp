/**
 *	@file	end.hpp
 *
 *	@brief	ranges::end の定義
 */

#ifndef HAMON_RANGES_ACCESS_END_HPP
#define HAMON_RANGES_ACCESS_END_HPP

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/has_member_end.hpp>
#include <hamon/ranges/detail/has_adl_end.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.3 ranges::end[range.access.end]
struct end_fn
{
private:
	// [range.access.end]/2.3
	template <typename T, typename = hamon::enable_if_t<
		hamon::is_unbounded_array<hamon::remove_reference_t<T>>::value>>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<4>) = delete;

	// [range.access.end]/2.4
	template <typename T,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_bounded_array<hamon::remove_reference_t<T>>,
			hamon::is_lvalue_reference<T>>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::decay_t<T>
	impl(T&& t, hamon::detail::overload_priority<3>) HAMON_NOEXCEPT
	{
		return t + hamon::extent<hamon::remove_reference_t<T>>::value;
	}

	// [range.access.end]/2.5
	template <HAMON_CONSTRAINT(has_member_end, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(t.end()))

	// [range.access.end]/2.6
	template <HAMON_CONSTRAINT(has_adl_end, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(end(t)))

	// [range.access.end]/2.7
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>		// [range.access.end]/2.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<4>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.end]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::end_fn end{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ACCESS_END_HPP
