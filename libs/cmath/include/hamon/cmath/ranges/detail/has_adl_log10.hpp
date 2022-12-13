/**
 *	@file	has_adl_log10.hpp
 *
 *	@brief	has_adl_log10 の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_LOG10_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_LOG10_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace log10_detail
{

#if 0
void log10(const auto&) = delete;
#else
template <typename T> void log10(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_log10 =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ log10(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_log10_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(log10(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_log10 = typename has_adl_log10_impl<T>::type;

#endif

}	// namespace log10_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_LOG10_HPP
