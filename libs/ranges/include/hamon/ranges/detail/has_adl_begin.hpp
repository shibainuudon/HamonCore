/**
 *	@file	has_adl_begin.hpp
 *
 *	@brief	has_adl_begin の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_ADL_BEGIN_HPP
#define HAMON_RANGES_DETAIL_HAS_ADL_BEGIN_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if (defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION >= 120000) && defined(HAMON_HAS_CXX20_CONCEPTS)) || \
    (defined(HAMON_CLANG_VERSION))
void begin() = delete;
#else
void begin();
#endif

// [range.access.begin]/2.5

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_begin =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(begin(t)) } -> hamon::input_or_output_iterator;
	};

#else

template <typename T>
struct has_adl_begin_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<
				hamon::remove_reference_t<U>
			>::value>,
		typename I = decltype(HAMON_AUTO_CAST(begin(hamon::declval<U&>())))
	>
	static auto test(int) -> hamon::input_or_output_iterator<I>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_begin = typename has_adl_begin_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_ADL_BEGIN_HPP
