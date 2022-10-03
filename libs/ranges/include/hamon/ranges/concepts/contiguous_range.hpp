/**
 *	@file	contiguous_range.hpp
 *
 *	@brief	contiguous_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon
{
namespace ranges
{

using std::ranges::contiguous_range;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/type_traits/add_pointer.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{
namespace ranges
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept contiguous_range =
	ranges::random_access_range<T> &&
	hamon::contiguous_iterator<ranges::iterator_t<T>> &&
	requires(T& t)
	{
		{ ranges::data(t) } -> hamon::same_as<hamon::add_pointer_t<ranges::range_reference_t<T>>>;
	};

#else

namespace detail
{

template <typename T>
struct contiguous_range_impl
{
private:
	template <
		typename U,
		typename = hamon::enable_if_t<ranges::random_access_range<U>::value>,
		typename = hamon::enable_if_t<hamon::contiguous_iterator<ranges::iterator_t<U>>::value>,
		typename P1 = decltype(ranges::data(std::declval<U&>())),
		typename P2 = hamon::add_pointer_t<ranges::range_reference_t<U>>
	>
	static auto test(int) -> hamon::same_as<P1, P2>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using contiguous_range =
	typename ranges::detail::contiguous_range_impl<T>::type;

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
using contiguous_range_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::contiguous_range<T>>;
#else
	hamon::ranges::contiguous_range<T>;
#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP
