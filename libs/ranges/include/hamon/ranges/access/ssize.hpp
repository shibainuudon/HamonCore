/**
 *	@file	ssize.hpp
 *
 *	@brief	ranges::ssize の定義
 */

#ifndef HAMON_RANGES_ACCESS_SSIZE_HPP
#define HAMON_RANGES_ACCESS_SSIZE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::ssize;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/size.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 25.3.11 ranges::ssize[range.prim.ssize]
struct ssize_fn
{
public:
	// [range.prim.ssize]/2
	template <
		typename T,
		typename S = hamon::make_signed_t<decltype(ranges::size(hamon::declval<T>()))>,
		typename D = hamon::conditional_t<
			(sizeof(hamon::ptrdiff_t) > sizeof(S)), hamon::ptrdiff_t, S>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator() (T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			static_cast<D>(ranges::size(t)))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

inline namespace cpo
{

// [range.prim.ssize]/1
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::ssize_fn ssize{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ACCESS_SSIZE_HPP
