/**
 *	@file	data.hpp
 *
 *	@brief	ranges::data の定義
 */

#ifndef HAMON_RANGES_DATA_HPP
#define HAMON_RANGES_DATA_HPP

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
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct data_fn
{
private:
	template <HAMON_CONSTRAINED_PARAM(has_member_data, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(std::declval<T&>().data()))
	->decltype(t.data())
	{
		return t.data();
	}

	template <HAMON_CONSTRAINED_PARAM(begin_data, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(ranges::begin(std::declval<T&>()))
	->decltype(hamon::to_address(ranges::begin(t)))
	{
		return hamon::to_address(ranges::begin(t));
	}

public:
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::data_fn data{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_DATA_HPP
