/**
 *	@file	cpp17_iterator.hpp
 *
 *	@brief	cpp17_iterator の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_CPP17_ITERATOR_HPP
#define HAMON_ITERATOR_DETAIL_CPP17_ITERATOR_HPP

#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [iterator.traits]/2

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename I>
concept cpp17_iterator =
	requires(I i)
	{
		{ *i } -> hamon::detail::can_reference;
		{ ++i } -> hamon::same_as<I&>;
		{ *i++ } -> hamon::detail::can_reference;
	} &&
	hamon::copyable<I>;

template <typename T>
using cpp17_iterator_t = hamon::bool_constant<cpp17_iterator<T>>;

#else

namespace cpp17_iterator_detail
{

template <typename I>
struct cpp17_iterator_impl
{
private:
	template <typename I2,
		typename T1 = decltype( *hamon::declval<I2&>()),
		typename T2 = decltype(++hamon::declval<I2&>()),
		typename T3 = decltype( *hamon::declval<I2&>()++)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::detail::can_reference<T1>,
		hamon::same_as<T2, I2&>,
		hamon::detail::can_reference<T3>,
		hamon::copyable<I2>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

}	// namespace cpp17_iterator_detail

template <typename I>
using cpp17_iterator =
	typename cpp17_iterator_detail::cpp17_iterator_impl<I>::type;

template <typename T>
using cpp17_iterator_t = cpp17_iterator<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_CPP17_ITERATOR_HPP
