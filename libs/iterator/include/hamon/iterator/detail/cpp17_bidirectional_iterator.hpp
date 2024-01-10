/**
 *	@file	cpp17_bidirectional_iterator.hpp
 *
 *	@brief	cpp17_bidirectional_iterator の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_CPP17_BIDIRECTIONAL_ITERATOR_HPP
#define HAMON_ITERATOR_DETAIL_CPP17_BIDIRECTIONAL_ITERATOR_HPP

#include <hamon/iterator/detail/cpp17_forward_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
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
concept cpp17_bidirectional_iterator =
	cpp17_forward_iterator<I> &&
	requires(I i)
	{
		{  --i } -> hamon::same_as<I&>;
		{  i-- } -> hamon::convertible_to<I const&>;
		{ *i-- } -> hamon::same_as<hamon::iter_reference_t<I>>;
	};

template <typename T>
using cpp17_bidirectional_iterator_t = hamon::bool_constant<cpp17_bidirectional_iterator<T>>;

#else

namespace cpp17_bidirectional_iterator_detail
{

template <typename I>
struct cpp17_bidirectional_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_forward_iterator<I2>::value>,
		typename T1 = decltype(--hamon::declval<I2&>()),
		typename T2 = decltype(  hamon::declval<I2&>()--),
		typename T3 = decltype( *hamon::declval<I2&>()--)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<T1, I2&>,
		hamon::convertible_to<T2, I2 const&>,
		hamon::same_as<T3, hamon::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

}	// namespace cpp17_bidirectional_iterator_detail

template <typename I>
using cpp17_bidirectional_iterator =
	typename cpp17_bidirectional_iterator_detail::cpp17_bidirectional_iterator_impl<I>::type;

template <typename T>
using cpp17_bidirectional_iterator_t = cpp17_bidirectional_iterator<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_CPP17_BIDIRECTIONAL_ITERATOR_HPP
