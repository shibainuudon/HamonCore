/**
 *	@file	empty.hpp
 *
 *	@brief	ranges::empty の定義
 */

#ifndef HAMON_RANGES_ACCESS_EMPTY_HPP
#define HAMON_RANGES_ACCESS_EMPTY_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::empty;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/detail/has_member_empty.hpp>
#include <hamon/ranges/detail/size0_empty.hpp>
#include <hamon/ranges/detail/eq_iter_empty.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct empty_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_member_empty, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF_EXPR(bool(t.empty()))
	->decltype(bool(t.empty()))
	{
		return bool(t.empty());
	}

	template <HAMON_CONSTRAINED_PARAM(size0_empty, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(ranges::size(t) == 0)
	->decltype(ranges::size(t) == 0)
	{
		return ranges::size(t) == 0;
	}

	template <HAMON_CONSTRAINED_PARAM(eq_iter_empty, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(
			bool(ranges::begin(t) == ranges::end(t)))
	->decltype(bool(ranges::begin(t) == ranges::end(t)))
	{
		return bool(ranges::begin(t) == ranges::end(t));
	}

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<2>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::empty_fn empty{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_EMPTY_HPP
