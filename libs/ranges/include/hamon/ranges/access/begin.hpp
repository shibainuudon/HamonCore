/**
 *	@file	begin.hpp
 *
 *	@brief	ranges::begin の定義
 */

#ifndef HAMON_RANGES_ACCESS_BEGIN_HPP
#define HAMON_RANGES_ACCESS_BEGIN_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::begin;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/has_member_begin.hpp>
#include <hamon/ranges/detail/has_adl_begin.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
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

// 25.3.2 ranges::begin[range.access.begin]
struct begin_fn
{
private:
	// [range.access.begin]/2.3
	template <typename T,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::is_array<hamon::remove_reference_t<T>>,
			hamon::is_lvalue_reference<T>>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::decay_t<T>
	impl(T&& t, hamon::detail::overload_priority<3>) HAMON_NOEXCEPT
	{
		return t + 0;
	}

	// [range.access.begin]/2.4
	template <HAMON_CONSTRAINED_PARAM(has_member_begin, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(t.begin()))
	
	// [range.access.begin]/2.5
	template <HAMON_CONSTRAINED_PARAM(has_adl_begin, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(begin(t)))

	// [range.access.begin]/2.6
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>		// [range.access.begin]/2.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<3>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.begin]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::begin_fn begin{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_BEGIN_HPP
