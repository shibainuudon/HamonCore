/**
 *	@file	size.hpp
 *
 *	@brief	ranges::size の定義
 */

#ifndef HAMON_RANGES_ACCESS_SIZE_HPP
#define HAMON_RANGES_ACCESS_SIZE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::size;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/detail/has_member_size.hpp>
#include <hamon/ranges/detail/has_adl_size.hpp>
#include <hamon/ranges/detail/sentinel_size.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/extent.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/is_unbounded_array.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.10 ranges::size[range.prim.size]
struct size_fn
{
private:
	// [range.prim.size]/2.1
	template <typename T, typename = hamon::enable_if_t<
		hamon::is_unbounded_array<hamon::remove_cvref_t<T>>::value>>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<5>) = delete;

	// [range.prim.size]/2.2
	template <typename T, typename = hamon::enable_if_t<
		hamon::is_bounded_array<hamon::remove_cvref_t<T>>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&&, hamon::detail::overload_priority<4>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			HAMON_AUTO_CAST(hamon::extent<hamon::remove_cvref_t<T>>::value))

	// [range.prim.size]/2.3
	template <HAMON_CONSTRAINED_PARAM(has_member_size, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(t.size()))

	// [range.prim.size]/2.4
	template <HAMON_CONSTRAINED_PARAM(has_adl_size, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(size(t)))

	// [range.prim.size]/2.5
	template <HAMON_CONSTRAINED_PARAM(sentinel_size, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			detail::to_unsigned_like(ranges::end(t) - ranges::begin(t)))

	// [range.prim.size]/2.6
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<5>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.prim.size]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::size_fn size{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_SIZE_HPP
