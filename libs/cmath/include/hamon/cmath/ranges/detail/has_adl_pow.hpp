/**
 *	@file	has_adl_pow.hpp
 *
 *	@brief	has_adl_pow の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_POW_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_POW_HPP

#include <hamon/cmath/ranges/detail/is_not_void.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace pow_detail
{

#if 0
void pow(const auto&, const auto&) = delete;
#else
template <typename T1, typename T2> void pow(T1 const&, T2 const&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2>
HAMON_CONCEPT_OR_BOOL has_adl_pow =
	(hamon::detail::class_or_enum<T1> ||
	 hamon::detail::class_or_enum<T2> ) &&
	requires(T1 const& x, T2 const& y)
	{
		{ pow(x, y) } -> hamon::detail::is_not_void;
	};

#else

template <typename T1, typename T2>
struct has_adl_pow_impl
{
private:
	template <typename U1, typename U2,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U1> ||
			hamon::detail::class_or_enum<U2>
		>,
		typename S = decltype(pow(hamon::declval<U1 const&>(), hamon::declval<U2 const&>())),
		typename = hamon::enable_if_t<hamon::detail::is_not_void<S>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U1, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T1, T2>(0));
};

template <typename T1, typename T2>
HAMON_CONCEPT_OR_BOOL has_adl_pow = has_adl_pow_impl<T1, T2>::type::value;

#endif

}	// namespace pow_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_POW_HPP
