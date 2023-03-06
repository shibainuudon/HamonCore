/**
 *	@file	cpp17_randacc_iterator.hpp
 *
 *	@brief	cpp17_randacc_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_RANDACC_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_RANDACC_ITERATOR_HPP

#include <hamon/iterator/concepts/detail/cpp17_bidi_iterator.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/totally_ordered.hpp>
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
concept cpp17_randacc_iterator =
	cpp17_bidi_iterator<Iter> &&
	hamon::totally_ordered<Iter> &&
	requires(Iter it, typename hamon::incrementable_traits<Iter>::difference_type n)
	{
		{ it += n } -> hamon::same_as<Iter&>;
		{ it -= n } -> hamon::same_as<Iter&>;
		{ it +  n } -> hamon::same_as<Iter>;
		{ n +  it } -> hamon::same_as<Iter>;
		{ it -  n } -> hamon::same_as<Iter>;
		{ it - it } -> hamon::same_as<decltype(n)>;
		{  it[n]  } -> hamon::convertible_to<hamon::iter_reference_t<Iter>>;
	};

#else

namespace cpp17_randacc_iterator_detail
{

template <typename Iter>
struct cpp17_randacc_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_bidi_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::totally_ordered<I2>::value>,
		typename D = typename hamon::incrementable_traits<I2>::difference_type,
		typename T1 = decltype(std::declval<I2&>() += std::declval<D& >()),
		typename T2 = decltype(std::declval<I2&>() -= std::declval<D& >()),
		typename T3 = decltype(std::declval<I2&>() +  std::declval<D& >()),
		typename T4 = decltype(std::declval<D& >() +  std::declval<I2&>()),
		typename T5 = decltype(std::declval<I2&>() -  std::declval<D& >()),
		typename T6 = decltype(std::declval<I2&>() -  std::declval<I2&>()),
		typename T7 = decltype(std::declval<I2&>()[std::declval<D&>()])
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<T1, I2&>,
		hamon::same_as<T2, I2&>,
		hamon::same_as<T3, I2>,
		hamon::same_as<T4, I2>,
		hamon::same_as<T5, I2>,
		hamon::same_as<T6, D>,
		hamon::convertible_to<T7, hamon::iter_reference_t<I2>>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_randacc_iterator_detail

template <typename Iter>
using cpp17_randacc_iterator =
	typename cpp17_randacc_iterator_detail::cpp17_randacc_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_RANDACC_ITERATOR_HPP
