/**
 *	@file	indirectly_binary_right_foldable.hpp
 *
 *	@brief	indirectly_binary_right_foldable の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_DETAIL_INDIRECTLY_BINARY_RIGHT_FOLDABLE_HPP
#define HAMON_ALGORITHM_RANGES_DETAIL_INDIRECTLY_BINARY_RIGHT_FOLDABLE_HPP

#include <hamon/algorithm/ranges/detail/indirectly_binary_left_foldable.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <typename F>
class flipped
{
    F f;    // exposition only
public:
    template <typename T, typename U>
    auto operator()(T&&, U&&)
    HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
        hamon::invoke_result_t<F& HAMON_PP_COMMA() U HAMON_PP_COMMA() T>,
        hamon::invocable<F&, U, T>);
};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename F, typename T, typename I>
concept indirectly_binary_right_foldable =
    indirectly_binary_left_foldable<flipped<F>, T, I>;

#else

template <typename F, typename T, typename I>
using indirectly_binary_right_foldable =
    indirectly_binary_left_foldable<flipped<F>, T, I>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_DETAIL_INDIRECTLY_BINARY_RIGHT_FOLDABLE_HPP
