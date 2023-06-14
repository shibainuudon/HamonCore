/**
 *	@file	almost_equal.hpp
 *
 *	@brief	ranges::almost_equal の定義
 */

#ifndef HAMON_CMATH_RANGES_ALMOST_EQUAL_HPP
#define HAMON_CMATH_RANGES_ALMOST_EQUAL_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_almost_equal.hpp>
#include <hamon/cmath/almost_equal.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace almost_equal_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct almost_equal_fn
{
private:
	template <typename T1, typename T2,
		typename = hamon::enable_if_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
			has_adl_almost_equal<T1, T2>
#else
			has_adl_almost_equal<T1, T2>::value
#endif
		>
	>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(almost_equal(x, y))

	template <typename T1, typename T2>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::almost_equal(x, y))

public:
	template <typename T1, typename T2>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T1 const& x, T2 const& y) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, y, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace almost_equal_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
almost_equal_detail::almost_equal_fn almost_equal{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_ALMOST_EQUAL_HPP
