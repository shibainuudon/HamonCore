/**
 *	@file	input_range.hpp
 *
 *	@brief	input_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_INPUT_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_INPUT_RANGE_HPP

#include <hamon/ranges/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_USE_STD_RANGES)
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{
namespace ranges
{

// [range.refinements]/1

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::input_range;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept input_range =
	ranges::range<T> &&
	hamon::input_iterator<ranges::iterator_t<T>>;

#else

namespace detail
{

template <typename T>
struct input_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<ranges::range<U>::value>,
		typename = hamon::enable_if_t<hamon::input_iterator<ranges::iterator_t<U>>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using input_range = typename ranges::detail::input_range_impl<T>::type;

#endif

template <typename T>
using input_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::input_range<T>>;
#else
	hamon::ranges::input_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_INPUT_RANGE_HPP
