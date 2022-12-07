/**
 *	@file	has_adl_cos.hpp
 *
 *	@brief	has_adl_cos の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_COS_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_COS_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace cos_detail
{

#if 0
void cos(const auto&) = delete;
#else
template <typename T> void cos(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_cos =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ cos(t) } -> hamon::arithmetic;
	};

#else

template <typename T>
struct has_adl_cos_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(cos(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::arithmetic<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_cos = typename has_adl_cos_impl<T>::type;

#endif

}	// namespace cos_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_COS_HPP
