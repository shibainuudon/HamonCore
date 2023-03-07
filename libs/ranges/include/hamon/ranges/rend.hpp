/**
 *	@file	rend.hpp
 *
 *	@brief	ranges::rend の定義
 */

#ifndef HAMON_RANGES_REND_HPP
#define HAMON_RANGES_REND_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/iterator/reverse_iterator.hpp>

#if defined(HAMON_USE_STD_RANGES) && defined(HAMON_USE_STD_REVERSE_ITERATOR)

namespace hamon {
namespace ranges {

using std::ranges::rend;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/detail/has_member_rend.hpp>
#include <hamon/ranges/detail/has_adl_rend.hpp>
#include <hamon/ranges/detail/reversable.hpp>
#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
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

struct rend_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_member_rend, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(hamon::declval<T&>().rend()))
	->decltype(t.rend())
	{
		return t.rend();
	}

	template <HAMON_CONSTRAINED_PARAM(has_adl_rend, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(rend(hamon::declval<T&>())))
	->decltype(rend(t))
	{
		return rend(t);
	}

	template <HAMON_CONSTRAINED_PARAM(reversable, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		noexcept(
			noexcept(ranges::begin(t)) &&
			hamon::is_nothrow_copy_constructible<decltype(ranges::begin(t))>::value
		)
	->decltype(hamon::make_reverse_iterator(ranges::begin(t)))
	{
		return hamon::make_reverse_iterator(ranges::begin(t));
	}

public:
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<2>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::rend_fn rend{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_REND_HPP
