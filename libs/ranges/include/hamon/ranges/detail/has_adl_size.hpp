/**
 *	@file	has_adl_size.hpp
 *
 *	@brief	has_adl_size の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_SIZE_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_SIZE_HPP

#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/detail/is_integer_like.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if (defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000) && defined(HAMON_HAS_CXX20_CONCEPTS)) || \
    (defined(HAMON_CLANG_VERSION))
void size() = delete;
#else
void size();
#endif

// [range.prim.size]/2.4

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_size =
	hamon::detail::class_or_enum<hamon::remove_cvref_t<T>> &&
	!HAMON_RANGES_DISABLE_SIZED_RANGE(hamon::remove_cvref_t<T>) &&
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(size(t)) } -> hamon::detail::is_integer_like;
	};

#else

template <typename T>
struct has_adl_size_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<hamon::remove_cvref_t<U>>
		>,
		typename = hamon::enable_if_t<
			!HAMON_RANGES_DISABLE_SIZED_RANGE(hamon::remove_cvref_t<U>)
		>,
		typename V = decltype(HAMON_AUTO_CAST(size(hamon::declval<U&>()))),
		typename = hamon::enable_if_t<
			hamon::detail::is_integer_like<V>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_size = typename has_adl_size_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_SIZE_HPP
