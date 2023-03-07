/**
 *	@file	cpp17_iterator.hpp
 *
 *	@brief	cpp17_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_ITERATOR_HPP

#include <hamon/concepts/detail/can_reference.hpp>
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

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_iterator =
	requires(Iter it)
	{
		{ *it } -> hamon::detail::can_reference;
		{ ++it } -> hamon::same_as<Iter&>;
		{ *it++ } -> hamon::detail::can_reference;
	} &&
	hamon::copyable<Iter>;

#else

namespace cpp17_iterator_detail
{

template <typename Iter>
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
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_iterator_detail

template <typename Iter>
using cpp17_iterator =
	typename cpp17_iterator_detail::cpp17_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_ITERATOR_HPP
