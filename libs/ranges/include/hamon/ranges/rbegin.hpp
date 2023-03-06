/**
 *	@file	rbegin.hpp
 *
 *	@brief	ranges::rbegin の定義
 */

#ifndef HAMON_RANGES_RBEGIN_HPP
#define HAMON_RANGES_RBEGIN_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/iterator/reverse_iterator.hpp>

#if defined(HAMON_USE_STD_RANGES) && defined(HAMON_USE_STD_REVERSE_ITERATOR)

namespace hamon {
namespace ranges {

using std::ranges::rbegin;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/end.hpp>
#include <hamon/ranges/detail/has_member_rbegin.hpp>
#include <hamon/ranges/detail/has_adl_rbegin.hpp>
#include <hamon/ranges/detail/reversable.hpp>
#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct rbegin_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_member_rbegin, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(std::declval<T&>().rbegin()))
	->decltype(t.rbegin())
	{
		return t.rbegin();
	}

	template <HAMON_CONSTRAINED_PARAM(has_adl_rbegin, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(rbegin(std::declval<T&>())))
	->decltype(rbegin(t))
	{
		return rbegin(t);
	}

	template <HAMON_CONSTRAINED_PARAM(reversable, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		noexcept(
			noexcept(ranges::end(t)) &&
			hamon::is_nothrow_copy_constructible<decltype(ranges::end(t))>::value)
	->decltype(hamon::make_reverse_iterator(ranges::end(t)))
	{
		return hamon::make_reverse_iterator(ranges::end(t));
	}

public:
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(std::forward<T>(t), hamon::detail::overload_priority<2>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::rbegin_fn rbegin{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_RBEGIN_HPP
