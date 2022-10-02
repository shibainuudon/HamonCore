/**
 *	@file	compare_three_way_result.hpp
 *
 *	@brief	compare_three_way_result の定義
 */

#ifndef HAMON_COMPARE_COMPARE_THREE_WAY_RESULT_HPP
#define HAMON_COMPARE_COMPARE_THREE_WAY_RESULT_HPP

#include <hamon/compare/config.hpp>

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(HAMON_USE_STD_COMPARE)

#include <compare>

namespace hamon
{

using std::compare_three_way_result;
using std::compare_three_way_result_t;

}	// namespace hamon

#else	// defined(HAMON_USE_STD_COMPARE)

#include <hamon/compare/detail/compare_three_way_result_impl.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename T, typename U = T>
struct compare_three_way_result
	: detail::compare_three_way_result_impl<T, U>
{};

template <typename T, typename U = T>
using compare_three_way_result_t =
	typename detail::compare_three_way_result_impl<T, U>::type;

}	// namespace hamon

#endif	// defined(HAMON_USE_STD_COMPARE)

#endif	// defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // HAMON_COMPARE_COMPARE_THREE_WAY_RESULT_HPP
