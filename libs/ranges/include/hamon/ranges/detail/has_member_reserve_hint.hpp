/**
 *	@file	has_member_reserve_hint.hpp
 *
 *	@brief	has_member_reserve_hint の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_RESERVE_HINT_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_RESERVE_HINT_HPP

#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/detail/is_integer_like.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.prim.size.hint]/2.2

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_reserve_hint =
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(t.reserve_hint()) } -> hamon::detail::is_integer_like;
	};

#else

template <typename T>
struct has_member_reserve_hint_impl
{
private:
	template <typename U,
		typename I = decltype(HAMON_AUTO_CAST(hamon::declval<U&>().reserve_hint()))
	>
	static auto test(int) -> hamon::detail::is_integer_like<I>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_reserve_hint = typename has_member_reserve_hint_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_RESERVE_HINT_HPP
