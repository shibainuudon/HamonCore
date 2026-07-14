/**
 *	@file	has_adl_end.hpp
 *
 *	@brief	has_adl_end の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_END_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_END_HPP

#include <hamon/ranges/iterator_t.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
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
void end() = delete;
#else
void end();
#endif

// [range.access.end]/2.6

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_adl_end =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(end(t)) } -> hamon::sentinel_for<hamon::ranges::iterator_t<T>>;
	};

#else

template <typename T>
struct has_adl_end_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<hamon::remove_reference_t<U>>
		>,
		typename S = decltype(HAMON_AUTO_CAST(end(hamon::declval<U&>()))),
		typename = hamon::enable_if_t<hamon::sentinel_for<S, hamon::ranges::iterator_t<U>>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_adl_end =
	has_adl_end_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_END_HPP
