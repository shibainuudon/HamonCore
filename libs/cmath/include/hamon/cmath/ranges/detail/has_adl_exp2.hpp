/**
 *	@file	has_adl_exp2.hpp
 *
 *	@brief	has_adl_exp2 の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_EXP2_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_EXP2_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace ranges
{

namespace exp2_detail
{

#if 0
void exp2(const auto&) = delete;
#else
template <typename T> void exp2(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_exp2 =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ exp2(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_exp2_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(exp2(hamon::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_exp2 = typename has_adl_exp2_impl<T>::type;

#endif

}	// namespace exp2_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_EXP2_HPP
