/**
 *	@file	cpp17_forward_iterator.hpp
 *
 *	@brief	cpp17_forward_iterator の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_CPP17_FORWARD_ITERATOR_HPP
#define HAMON_ITERATOR_DETAIL_CPP17_FORWARD_ITERATOR_HPP

#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
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
concept cpp17_forward_iterator =
	cpp17_input_iterator<I> &&
	hamon::constructible_from<I> &&
	hamon::is_lvalue_reference<hamon::iter_reference_t<I>>::value &&
	hamon::same_as<
		hamon::remove_cvref_t<hamon::iter_reference_t<I>>,
		typename hamon::indirectly_readable_traits<I>::value_type
	> &&
	requires(I i)
	{
		{  i++ } -> hamon::convertible_to<I const&>;
		{ *i++ } -> hamon::same_as<hamon::iter_reference_t<I>>;
	};

template <typename T>
using cpp17_forward_iterator_t = hamon::bool_constant<cpp17_forward_iterator<T>>;

#else

namespace cpp17_forward_iterator_detail
{

template <typename I>
struct cpp17_forward_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_input_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::constructible_from<I2>::value>,
		typename R = hamon::iter_reference_t<I2>,
		typename = hamon::enable_if_t<hamon::is_lvalue_reference<R>::value>,
		typename = hamon::enable_if_t<hamon::same_as<
			hamon::remove_cvref_t<R>,
			typename hamon::indirectly_readable_traits<I2>::value_type
		>::value>,
		typename T1 = decltype( hamon::declval<I2&>()++),
		typename T2 = decltype(*hamon::declval<I2&>()++)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::convertible_to<T1, I2 const&>,
		hamon::same_as<T2, R>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

}	// namespace cpp17_forward_iterator_detail

template <typename I>
using cpp17_forward_iterator =
	typename cpp17_forward_iterator_detail::cpp17_forward_iterator_impl<I>::type;

template <typename T>
using cpp17_forward_iterator_t = cpp17_forward_iterator<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_CPP17_FORWARD_ITERATOR_HPP
