/**
 *	@file	ssize.hpp
 *
 *	@brief	ranges::ssize の定義
 */

#ifndef HAMON_RANGES_SSIZE_HPP
#define HAMON_RANGES_SSIZE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::ssize;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <utility>

namespace hamon {
namespace ranges {

namespace detail {

struct ssize_fn
{
private:
	template <typename T>
	struct result_type
	{
		using iter_type = decltype(ranges::begin(std::declval<T&&>()));
		using diff_type = hamon::iter_difference_t<iter_type>;
		using type = hamon::conditional_t<
			std::is_integral<diff_type>::value &&
			std::numeric_limits<diff_type>::digits < std::numeric_limits<std::ptrdiff_t>::digits,
			std::ptrdiff_t,
			diff_type
		>;
	};

	template <typename T>
	using result_type_t = typename result_type<T>::type;

public:
	template <
		typename T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = decltype(ranges::begin(std::declval<T&&>()))
		, typename = decltype(ranges::size(std::declval<T&&>()))
#endif
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires (T&& e)
	{
		ranges::begin(std::forward<T>(e));
		ranges::size(std::forward<T>(e));
	}
#endif
	HAMON_CONSTEXPR result_type_t<T> operator()(T&& e) const
		HAMON_NOEXCEPT_IF_EXPR(ranges::size(std::forward<T>(e)))
	{
		return static_cast<result_type_t<T>>(ranges::size(std::forward<T>(e)));
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::ssize_fn ssize{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_SSIZE_HPP
