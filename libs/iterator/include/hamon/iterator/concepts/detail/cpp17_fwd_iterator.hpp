/**
 *	@file	cpp17_fwd_iterator.hpp
 *
 *	@brief	cpp17_fwd_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_FWD_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_FWD_ITERATOR_HPP

#include <hamon/iterator/concepts/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_fwd_iterator =
	cpp17_input_iterator<Iter> &&
	hamon::constructible_from<Iter> &&
	std::is_lvalue_reference<hamon::iter_reference_t<Iter>>::value &&
	hamon::same_as<
		hamon::remove_cvref_t<hamon::iter_reference_t<Iter>>,
		typename hamon::indirectly_readable_traits<Iter>::value_type
	> &&
	requires(Iter it)
	{
		{  it++ } -> hamon::convertible_to<Iter const&>;
		{ *it++ } -> hamon::same_as<hamon::iter_reference_t<Iter>>;
	};

#else

namespace cpp17_fwd_iterator_detail
{

template <typename Iter>
struct cpp17_fwd_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_input_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::constructible_from<I2>::value>,
		typename R = hamon::iter_reference_t<I2>,
		typename = hamon::enable_if_t<std::is_lvalue_reference<R>::value>,
		typename = hamon::enable_if_t<hamon::same_as<
			hamon::remove_cvref_t<R>,
			typename hamon::indirectly_readable_traits<I2>::value_type
		>::value>,
		typename T1 = decltype( std::declval<I2&>()++),
		typename T2 = decltype(*std::declval<I2&>()++)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::convertible_to<T1, I2 const&>,
		hamon::same_as<T2, R>
	>;

	template <typename I2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_fwd_iterator_detail

template <typename Iter>
using cpp17_fwd_iterator =
	typename cpp17_fwd_iterator_detail::cpp17_fwd_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_FWD_ITERATOR_HPP
