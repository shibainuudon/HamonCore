/**
 *	@file	bidirectional_range.hpp
 *
 *	@brief	bidirectional_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::bidirectional_range;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept bidirectional_range =
	ranges::forward_range<T> &&
	hamon::bidirectional_iterator<ranges::iterator_t<T>>;

#else

namespace detail
{

template <typename T>
struct bidirectional_range_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			ranges::forward_range<U>::value
		>,
		typename = hamon::enable_if_t<
			hamon::bidirectional_iterator<ranges::iterator_t<U>>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using bidirectional_range =
	typename ranges::detail::bidirectional_range_impl<T>::type;

#endif

}	// namespace ranges
}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{
namespace ranges
{

template <typename T>
using bidirectional_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::bidirectional_range<T>>;
#else
	hamon::ranges::bidirectional_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP
