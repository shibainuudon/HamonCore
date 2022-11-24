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
#include <hamon/type_traits/make_signed.hpp>
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
public:
	template <
		typename T,
		typename size_type = decltype(ranges::size(std::declval<T&>())),
		typename result_type =
			hamon::conditional_t<
				hamon::integral_t<size_type>::value,
				hamon::conditional_t<
					(std::numeric_limits<size_type>::digits < std::numeric_limits<std::ptrdiff_t>::digits),
					std::ptrdiff_t,
					hamon::make_signed_t<size_type>
				>,
				hamon::ranges::detail::max_diff_type
			>
	>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires (T& e)
	{
		ranges::size(e);
	}
#endif
	HAMON_NODISCARD HAMON_CONSTEXPR result_type
	operator() (T&& t) const
		HAMON_NOEXCEPT_IF_EXPR(ranges::size(t))
	{
		return static_cast<result_type>(ranges::size(t));
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
