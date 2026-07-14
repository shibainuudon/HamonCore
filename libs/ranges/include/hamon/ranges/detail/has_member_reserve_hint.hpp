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
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.prim.size.hint]/2.2

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_reserve_hint =
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
		typename I = decltype(HAMON_AUTO_CAST(hamon::declval<U&>().reserve_hint())),
		typename = hamon::enable_if_t<hamon::detail::is_integer_like<I>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_reserve_hint =
	has_member_reserve_hint_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_RESERVE_HINT_HPP
