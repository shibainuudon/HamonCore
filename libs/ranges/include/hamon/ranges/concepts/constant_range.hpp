/**
 *	@file	constant_range.hpp
 *
 *	@brief	constant_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_CONSTANT_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_CONSTANT_RANGE_HPP

#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/config.hpp>
#include <hamon/iterator/detail/constant_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::constant_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

// [range.refinements]/7

template <typename T>
concept constant_range =
	hamon::ranges::input_range<T> &&
	hamon::detail::constant_iterator<hamon::ranges::iterator_t<T>>;

#else

namespace detail
{

template <typename T>
struct constant_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::ranges::input_range_t<U>::value>,
		typename = hamon::enable_if_t<hamon::detail::constant_iterator_t<hamon::ranges::iterator_t<U>>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using constant_range = typename ranges::detail::constant_range_impl<T>::type;

#endif

template <typename T>
using constant_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::constant_range<T>>;
#else
	hamon::ranges::constant_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_constant_range_HPP
