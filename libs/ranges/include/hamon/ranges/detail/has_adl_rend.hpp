/**
 *	@file	has_adl_rend.hpp
 *
 *	@brief	has_adl_rend の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_REND_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_REND_HPP

#include <hamon/ranges/rbegin.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if (defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000) && defined(HAMON_HAS_CXX20_CONCEPTS)) || \
    (defined(HAMON_CLANG_VERSION))
void rend() = delete;
#else
void rend();
#endif

// [range.access.rend]/2.4

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_rend =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(rend(t)) } -> hamon::sentinel_for<decltype(ranges::rbegin(t))>;
	};

#else

template <typename T>
struct has_adl_rend_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<hamon::remove_reference_t<U>>
		>,
		typename S = decltype(HAMON_AUTO_CAST(rend(hamon::declval<U&>()))),
		typename I = decltype(ranges::rbegin(hamon::declval<U&>()))
	>
	static auto test(int) -> hamon::sentinel_for<S, I>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_rend = typename has_adl_rend_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_REND_HPP
