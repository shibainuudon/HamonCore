/**
 *	@file	begin.hpp
 *
 *	@brief	ranges::begin の定義
 */

#ifndef HAMON_RANGES_BEGIN_HPP
#define HAMON_RANGES_BEGIN_HPP

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
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_all_extents.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct begin_fn
{
private:
	template <
		typename T,
		typename = hamon::enable_if_t<
			std::is_array<hamon::remove_reference_t<T>>::value
		>
	>
	static HAMON_CONSTEXPR hamon::decay_t<T>
	impl(T&& t, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
	{
		static_assert(std::is_lvalue_reference<T>::value, "");
		return t + 0;
	}

	template <HAMON_CONSTRAINED_PARAM(has_member_begin, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(std::declval<T&>().begin()))
	->decltype(t.begin())
	{
		return t.begin();
	}
	
	template <HAMON_CONSTRAINED_PARAM(has_adl_begin, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(begin(std::declval<T&>())))
	->decltype(begin(t))
	{
		return begin(t);
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
detail::begin_fn begin{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_BEGIN_HPP
