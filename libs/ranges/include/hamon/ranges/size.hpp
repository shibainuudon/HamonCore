/**
 *	@file	size.hpp
 *
 *	@brief	ranges::size の定義
 */

#ifndef HAMON_RANGES_SIZE_HPP
#define HAMON_RANGES_SIZE_HPP

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
#include <hamon/type_traits/remove_reference.hpp>
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

struct size_fn
{
private:
	template <
		typename T,
		typename = hamon::enable_if_t<
			hamon::is_bounded_array<hamon::remove_reference_t<T>>::value
		>
	>
	static HAMON_CONSTEXPR auto
	impl(T&&, hamon::detail::overload_priority<3>) HAMON_NOEXCEPT
	->decltype(hamon::extent<hamon::remove_reference_t<T>>::value)
	{
		return hamon::extent<hamon::remove_reference_t<T>>::value;
	}

	template <HAMON_CONSTRAINED_PARAM(has_member_size, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(hamon::declval<T&>().size()))
	->decltype(t.size())
	{
		return t.size();
	}

	template <HAMON_CONSTRAINED_PARAM(has_adl_size, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(hamon::detail::decay_copy(size(hamon::declval<T&>())))
	->decltype(size(t))
	{
		return size(t);
	}

	template <HAMON_CONSTRAINED_PARAM(sentinel_size, T)>
	static HAMON_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(ranges::end(hamon::declval<T&>()) - ranges::begin(hamon::declval<T&>()))
	->decltype(detail::to_unsigned_like(ranges::end(t)-ranges::begin(t)))
	{
		return detail::to_unsigned_like(ranges::end(t)-ranges::begin(t));
	}

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CONSTEXPR auto operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<3>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::size_fn size{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_SIZE_HPP
