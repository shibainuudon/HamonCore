/**
 *	@file	indirectly_binary_left_foldable.hpp
 *
 *	@brief	indirectly_binary_left_foldable の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_DETAIL_INDIRECTLY_BINARY_LEFT_FOLDABLE_HPP
#define HAMON_ALGORITHM_RANGES_DETAIL_INDIRECTLY_BINARY_LEFT_FOLDABLE_HPP

#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/iterator/concepts/indirectly_readable.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename F, typename T, typename I, typename U>
concept indirectly_binary_left_foldable_impl =
	hamon::movable<T> &&
	hamon::movable<U> &&
	hamon::convertible_to<T, U> &&
	hamon::invocable<F&, U, hamon::iter_reference_t<I>> &&
	hamon::assignable_from<U&, hamon::invoke_result_t<F&, U, hamon::iter_reference_t<I>>>;

template <typename F, typename T, typename I>
concept indirectly_binary_left_foldable =
	hamon::copy_constructible<F> &&
	hamon::indirectly_readable<I> &&
	hamon::invocable<F&, T, hamon::iter_reference_t<I>> &&
	hamon::convertible_to<
		hamon::invoke_result_t<F&, T, hamon::iter_reference_t<I>>,
		hamon::decay_t<hamon::invoke_result_t<F&, T, hamon::iter_reference_t<I>>>
	> &&
	indirectly_binary_left_foldable_impl<
		F, T, I,
		hamon::decay_t<hamon::invoke_result_t<F&, T, hamon::iter_reference_t<I>>>
	>;

#else

template <typename F, typename T, typename I, typename U>
struct indirectly_binary_left_foldable_impl_detail
{
private:
	template <typename F2, typename T2, typename I2, typename U2,
		typename = hamon::enable_if_t<hamon::movable<T2>::value>,
		typename = hamon::enable_if_t<hamon::movable<U2>::value>,
		typename = hamon::enable_if_t<hamon::convertible_to<T2, U2>::value>,
		typename = hamon::enable_if_t<hamon::invocable<F2&, U2, hamon::iter_reference_t<I2>>::value>,
		typename = hamon::enable_if_t<hamon::assignable_from<
			U2&, hamon::invoke_result_t<F2&, U2, hamon::iter_reference_t<I2>>
		>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename F2, typename T2, typename I2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<F, T, I, U>(0));
};

template <typename F, typename T, typename I, typename U>
using indirectly_binary_left_foldable_impl =
	typename indirectly_binary_left_foldable_impl_detail<F, T, I, U>::type;

template <typename F, typename T, typename I>
struct indirectly_binary_left_foldable_detail
{
private:
	template <typename F2, typename T2, typename I2,
		typename = hamon::enable_if_t<hamon::copy_constructible<F2>::value>,
		typename = hamon::enable_if_t<hamon::indirectly_readable<I2>::value>,
		typename = hamon::enable_if_t<hamon::invocable<F2&, T2, hamon::iter_reference_t<I2>>::value>,
		typename R = hamon::invoke_result_t<F2&, T2, hamon::iter_reference_t<I2>>,
		typename = hamon::enable_if_t<hamon::convertible_to<R, hamon::decay_t<R>>::value>,
		typename = hamon::enable_if_t<
			indirectly_binary_left_foldable_impl<F2, T2, I2, hamon::decay_t<R>>::value
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename F2, typename T2, typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<F, T, I>(0));
};

template <typename F, typename T, typename I>
using indirectly_binary_left_foldable =
	typename indirectly_binary_left_foldable_detail<F, T, I>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_DETAIL_INDIRECTLY_BINARY_LEFT_FOLDABLE_HPP
