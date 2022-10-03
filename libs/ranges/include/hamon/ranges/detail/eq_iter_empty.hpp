/**
 *	@file	eq_iter_empty.hpp
 *
 *	@brief	eq_iter_empty の定義
 */

#ifndef HAMON_RANGES_DETAIL_EQ_ITER_EMPTY_HPP
#define HAMON_RANGES_DETAIL_EQ_ITER_EMPTY_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept eq_iter_empty =
	requires(T&& t)
	{
		{ ranges::begin(std::forward<T>(t)) } -> hamon::forward_iterator;
		bool(ranges::begin(std::forward<T>(t)) == ranges::end(std::forward<T>(t)));
	};

#else

template <typename T>
struct eq_iter_empty_impl
{
private:
	template <typename U,
		typename B = decltype(ranges::begin(std::declval<U&&>())),
		typename = hamon::enable_if_t<hamon::forward_iterator<B>::value>,
		typename = decltype(bool(ranges::begin(std::declval<U&&>()) == ranges::end(std::declval<U&&>())))
	>
	static auto test(int) -> std::true_type;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using eq_iter_empty = typename eq_iter_empty_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_EQ_ITER_EMPTY_HPP
