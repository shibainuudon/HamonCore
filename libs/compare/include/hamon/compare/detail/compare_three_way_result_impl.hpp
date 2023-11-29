/**
 *	@file	compare_three_way_result_impl.hpp
 *
 *	@brief	compare_three_way_result_impl の定義
 */

#ifndef HAMON_COMPARE_DETAIL_COMPARE_THREE_WAY_RESULT_IMPL_HPP
#define HAMON_COMPARE_DETAIL_COMPARE_THREE_WAY_RESULT_IMPL_HPP

#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename U>
using cmp3way_res_t =
	decltype(hamon::declval<T>() <=> hamon::declval<U>());

// Implementation of std::compare_three_way_result.
// It is undefined for a program to add specializations of
// std::compare_three_way_result, so the std::compare_three_way_result_t
// alias ignores std::compare_three_way_result and uses
// detail::compare_three_way_result_impl directly instead.
template <typename T, typename U>
struct compare_three_way_result_impl
{};

template <typename T, typename U>
requires requires { typename cmp3way_res_t<hamon::remove_reference_t<T> const&, hamon::remove_reference_t<U> const&>; }
struct compare_three_way_result_impl<T, U>
{
	using type = cmp3way_res_t<hamon::remove_reference_t<T> const&, hamon::remove_reference_t<U> const&>;
};

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_COMPARE_THREE_WAY_RESULT_IMPL_HPP
