/**
 *	@file	output_range.hpp
 *
 *	@brief	output_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_OUTPUT_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_OUTPUT_RANGE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::output_range;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Range, typename T>
concept output_range =
	ranges::range<Range> &&
	hamon::output_iterator<ranges::iterator_t<Range>, T>;

#else

namespace detail
{

template <typename Range, typename T>
struct output_range_impl
{
private:
	template <typename R, typename U,
		typename = hamon::enable_if_t<ranges::range<R>::value>,
		typename = hamon::enable_if_t<hamon::output_iterator<ranges::iterator_t<R>, U>::value>
	>
	static auto test(int) -> std::true_type;

	template <typename R, typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Range, T>(0));
};

}	// namespace detail

template <typename Range, typename T>
using output_range = typename ranges::detail::output_range_impl<Range, T>::type;

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{
namespace ranges
{

template <typename Range, typename T>
using output_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::output_range<Range, T>>;
#else
	hamon::ranges::output_range<Range, T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_OUTPUT_RANGE_HPP
