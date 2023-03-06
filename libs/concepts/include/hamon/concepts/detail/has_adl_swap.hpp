/**
 *	@file	has_adl_swap.hpp
 *
 *	@brief	has_adl_swap の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_HAS_ADL_SWAP_HPP
#define HAMON_CONCEPTS_DETAIL_HAS_ADL_SWAP_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace swap_detail
{

template <typename T> void swap(T&, T&) = delete;
template <typename T, std::size_t N> void swap(T(&)[N], T(&)[N]) = delete;

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept has_adl_swap =
	(hamon::detail::class_or_enum<hamon::remove_reference_t<T>> ||
	 hamon::detail::class_or_enum<hamon::remove_reference_t<U>>) &&
	requires(T&& t, U&& u)
	{
		swap(std::forward<T>(t), std::forward<U>(u));
	};

#else

template <typename T, typename U>
struct has_adl_swap_impl
{
private:
	template <typename T2, typename U2,
		typename = decltype(swap(std::declval<T2>(), std::declval<U2>()))
	>
	static auto test(int) -> hamon::disjunction<
		hamon::detail::class_or_enum<hamon::remove_reference_t<T2>>,
		hamon::detail::class_or_enum<hamon::remove_reference_t<U2>>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using has_adl_swap = typename has_adl_swap_impl<T, U>::type;

#endif

}	// namespace swap_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_HAS_ADL_SWAP_HPP
