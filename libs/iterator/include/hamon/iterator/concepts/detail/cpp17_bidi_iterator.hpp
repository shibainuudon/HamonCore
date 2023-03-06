/**
 *	@file	cpp17_bidi_iterator.hpp
 *
 *	@brief	cpp17_bidi_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_BIDI_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_BIDI_ITERATOR_HPP

#include <hamon/iterator/concepts/detail/cpp17_fwd_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_bidi_iterator =
	cpp17_fwd_iterator<Iter> &&
	requires(Iter it)
	{
		{  --it } -> hamon::same_as<Iter&>;
		{  it-- } -> hamon::convertible_to<Iter const&>;
		{ *it-- } -> hamon::same_as<hamon::iter_reference_t<Iter>>;
	};

#else

namespace cpp17_bidi_iterator_detail
{

template <typename Iter>
struct cpp17_bidi_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_fwd_iterator<I2>::value>,
		typename T1 = decltype(--std::declval<I2&>()),
		typename T2 = decltype(  std::declval<I2&>()--),
		typename T3 = decltype( *std::declval<I2&>()--)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<T1, I2&>,
		hamon::convertible_to<T2, I2 const&>,
		hamon::same_as<T3, hamon::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_bidi_iterator_detail

template <typename Iter>
using cpp17_bidi_iterator =
	typename cpp17_bidi_iterator_detail::cpp17_bidi_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_BIDI_ITERATOR_HPP
