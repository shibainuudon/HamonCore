/**
 *	@file	end.hpp
 *
 *	@brief	ranges::end の定義
 */

#ifndef HAMON_RANGES_END_HPP
#define HAMON_RANGES_END_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::end;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/detail/maybe_borrowed_range.hpp>
#include <hamon/ranges/detail/has_member_end.hpp>
#include <hamon/ranges/detail/has_adl_end.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_bounded_array.hpp>
#include <hamon/type_traits/remove_reference.hpp>
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

struct end_fn
{
private:
	template <
		typename T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::is_bounded_array<hamon::remove_reference_t<T>>::value>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::is_bounded_array<hamon::remove_reference_t<T>>::value
#endif
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<2>, T&& t) HAMON_NOEXCEPT
	->decltype(t + 0)
	{
		static_assert(std::is_lvalue_reference<T>::value, "");
		return t + std::extent<hamon::remove_reference_t<T>>::value;
	}

	template <HAMON_CONSTRAINED_PARAM(has_member_end, T)>
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<1>, T&& t)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(t.end()))
	->decltype(t.end())
	{
		return t.end();
	}

	template <HAMON_CONSTRAINED_PARAM(has_adl_end, T)>
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<0>, T&& t)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(end(t)))
	->decltype(end(t))
	{
		return end(t);
	}

public:
	template <HAMON_CONSTRAINED_PARAM(maybe_borrowed_range, T)>
	HAMON_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::detail::overload_priority<2>{}, std::forward<T>(t)))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::end_fn end{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_END_HPP
