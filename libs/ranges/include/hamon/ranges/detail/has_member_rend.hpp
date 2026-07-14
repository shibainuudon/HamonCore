/**
 *	@file	has_member_rend.hpp
 *
 *	@brief	has_member_rend の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_REND_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_REND_HPP

#include <hamon/ranges/rbegin.hpp>
#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.access.rend]/2.3

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_rend =
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(t.rend()) } -> hamon::sentinel_for<decltype(ranges::rbegin(t))>;
	};

#else

template <typename T>
struct has_member_rend_impl
{
private:
	template <typename U,
		typename S = decltype(HAMON_AUTO_CAST(hamon::declval<U&>().rend())),
		typename I = decltype(ranges::rbegin(hamon::declval<U&>())),
		typename = hamon::enable_if_t<hamon::sentinel_for<S, I>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_rend =
	has_member_rend_impl<T>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_REND_HPP
