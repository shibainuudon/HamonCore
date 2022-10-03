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
#include <hamon/ranges/detail/decay_copy.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
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

struct size_fn
{
private:
	template <
		typename T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::is_bounded_array<hamon::remove_reference_t<T>>::value
		>
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires hamon::is_bounded_array<hamon::remove_reference_t<T>>::value
#endif
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<3>, T&&) HAMON_NOEXCEPT
	->decltype(std::extent<hamon::remove_reference_t<T>>::value)
	{
		return std::extent<hamon::remove_reference_t<T>>::value;
	}

	template <HAMON_CONSTRAINED_PARAM(has_member_size, T)>
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<2>, T&& t)
		HAMON_NOEXCEPT_IF_EXPR(decay_copy(std::forward<T>(t).size()))
	->decltype(std::forward<T>(t).size())
	{
		return std::forward<T>(t).size();
	}

	template <HAMON_CONSTRAINED_PARAM(has_adl_size, T)>
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<1>, T&& t)
		HAMON_NOEXCEPT_IF_EXPR(decay_copy(size(std::forward<T>(t))))
	->decltype(size(std::forward<T>(t)))
	{
		return size(std::forward<T>(t));
	}

	template <HAMON_CONSTRAINED_PARAM(sentinel_size, T)>
	static HAMON_CONSTEXPR auto
	impl(hamon::detail::overload_priority<0>, T&& t)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			detail::to_unsigned_like(ranges::end(std::forward<T>(t)) - ranges::begin(std::forward<T>(t))))

public:
	template <typename T>
	HAMON_CONSTEXPR auto operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::detail::overload_priority<3>{}, std::forward<T>(t)))
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
