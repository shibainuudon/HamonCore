/**
 *	@file	rbegin.hpp
 *
 *	@brief	ranges::rbegin の定義
 */

#ifndef HAMON_RANGES_ACCESS_RBEGIN_HPP
#define HAMON_RANGES_ACCESS_RBEGIN_HPP

#include <hamon/ranges/end.hpp>
#include <hamon/ranges/detail/has_member_rbegin.hpp>
#include <hamon/ranges/detail/has_adl_rbegin.hpp>
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

// 25.3.6 ranges::rbegin[range.access.rbegin]
struct rbegin_fn
{
private:
	// [range.access.rbegin]/2.3
	template <HAMON_CONSTRAINT(has_member_rbegin, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<3>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(t.rbegin()))

	// [range.access.rbegin]/2.4
	template <HAMON_CONSTRAINT(has_adl_rbegin, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(HAMON_AUTO_CAST(rbegin(t)))

	// [range.access.rbegin]/2.5
	template <HAMON_CONSTRAINT(reversable, T)>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(ranges::end(t))
	->decltype(hamon::make_reverse_iterator(ranges::end(t)))
	{
		return hamon::make_reverse_iterator(ranges::end(t));
	}

	// [range.access.rbegin]/2.6
	template <typename T>
	static HAMON_CXX11_CONSTEXPR void
	impl(T&&, hamon::detail::overload_priority<0>) = delete;

public:
	template <HAMON_CONSTRAINT(maybe_borrowed_range, T)>	// [range.access.rbegin]/2.1
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<3>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.access.rbegin]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::rbegin_fn rbegin{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ACCESS_RBEGIN_HPP
