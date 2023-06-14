/**
 *	@file	fmod.hpp
 *
 *	@brief	ranges::fmod の定義
 */

#ifndef HAMON_CMATH_RANGES_FMOD_HPP
#define HAMON_CMATH_RANGES_FMOD_HPP

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/cmath/ranges/detail/has_adl_fmod.hpp>
#include <hamon/cmath/fmod.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace fmod_detail
{

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

struct fmod_fn
{
private:
	template <typename T1, typename T2,
		typename = hamon::enable_if_t<
#if defined(HAMON_HAS_CXX20_CONCEPTS)
			has_adl_fmod<T1, T2>
#else
			has_adl_fmod<T1, T2>::value
#endif
		>
	>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(fmod(x, y))

	template <typename T1, typename T2>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T1 const& x, T2 const& y, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::fmod(x, y))

public:
	template <typename T1, typename T2>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T1 const& x, T2 const& y) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(x, y, hamon::detail::overload_priority<1>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace fmod_detail

inline namespace cpo
{

// Customization point object
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
fmod_detail::fmod_fn fmod{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_FMOD_HPP
