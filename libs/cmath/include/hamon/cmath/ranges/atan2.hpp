/**
 *	@file	atan2.hpp
 *
 *	@brief	ranges::atan2 の定義
 */

#ifndef HAMON_CMATH_RANGES_ATAN2_HPP
#define HAMON_CMATH_RANGES_ATAN2_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_atan2.hpp>
#include <hamon/cmath/atan2.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace atan2_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct atan2_fn
{
private:
	template <typename T1, typename T2,
		typename = hamon::enable_if_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
			has_adl_atan2<T1, T2>
#else
			has_adl_atan2<T1, T2>::value
#endif
		>
	>
	static HAMON_CONSTEXPR auto
	impl(T1 const& y, T2 const& x, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(atan2(y, x))

	template <typename T1, typename T2>
	static HAMON_CONSTEXPR auto
	impl(T1 const& y, T2 const& x, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::atan2(y, x))

public:
	template <typename T1, typename T2>
	HAMON_NODISCARD HAMON_CONSTEXPR auto
	operator()(T1 const& y, T2 const& x) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(y, x, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace atan2_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CONSTEXPR
atan2_detail::atan2_fn atan2{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_ATAN2_HPP
