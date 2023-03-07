/**
 *	@file	has_adl_fmod.hpp
 *
 *	@brief	has_adl_fmod の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FMOD_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FMOD_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace ranges
{

namespace fmod_detail
{

#if 0
void fmod(const auto&, const auto&) = delete;
#else
template <typename T1, typename T2> void fmod(T1 const&, T2 const&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2>
concept has_adl_fmod =
	(hamon::detail::class_or_enum<T1> ||
	 hamon::detail::class_or_enum<T2> ) &&
	requires(T1 const& x, T2 const& y)
	{
		{ fmod(x, y) } -> hamon::detail::can_reference;
	};

#else

template <typename T1, typename T2>
struct has_adl_fmod_impl
{
private:
	template <typename U1, typename U2,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U1>::value ||
			hamon::detail::class_or_enum<U2>::value
		>,
		typename S = decltype(fmod(hamon::declval<U1 const&>(), hamon::declval<U2 const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U1, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T1, T2>(0));
};

template <typename T1, typename T2>
using has_adl_fmod = typename has_adl_fmod_impl<T1, T2>::type;

#endif

}	// namespace fmod_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FMOD_HPP
