/**
 *	@file	has_adl_isinf.hpp
 *
 *	@brief	has_adl_isinf の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ISINF_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ISINF_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace isinf_detail
{

#if 0
void isinf(const auto&) = delete;
#else
template <typename T> void isinf(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_isinf =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ isinf(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_isinf_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(isinf(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_isinf = typename has_adl_isinf_impl<T>::type;

#endif

}	// namespace isinf_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ISINF_HPP
