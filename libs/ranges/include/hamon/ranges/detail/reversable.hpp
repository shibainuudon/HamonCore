/**
 *	@file	reversable.hpp
 *
 *	@brief	reversable の定義
 */

#ifndef HAMON_RANGES_DETAIL_REVERSABLE_HPP
#define HAMON_RANGES_DETAIL_REVERSABLE_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept reversable =
	requires(T& t)
	{
		{ ranges::begin(t) } -> hamon::bidirectional_iterator;
		{ ranges::end(t) } -> hamon::same_as<decltype(ranges::begin(t))>;
	};

#else

template <typename T>
struct reversable_impl
{
private:
	template <typename U,
		typename B = decltype(ranges::begin(hamon::declval<U&>())),
		typename E = decltype(ranges::end(hamon::declval<U&>()))
	>
	static auto test(int) -> hamon::conjunction<
		hamon::bidirectional_iterator<B>,
		hamon::same_as<E, B>
	>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using reversable = typename reversable_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_REVERSABLE_HPP
