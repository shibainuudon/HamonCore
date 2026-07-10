/**
 *	@file	has_member_rbegin.hpp
 *
 *	@brief	has_member_rbegin の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP

#include <hamon/detail/auto_cast.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.access.rbegin]/2.3

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_rbegin =
	requires(T&& t)
	{
		{ HAMON_AUTO_CAST(t.rbegin()) } -> hamon::input_or_output_iterator;
	};

#else

template <typename T>
struct has_member_rbegin_impl
{
private:
	template <typename U,
		typename I = decltype(HAMON_AUTO_CAST(hamon::declval<U&>().rbegin())),
		typename = hamon::enable_if_t<hamon::input_or_output_iterator<I>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_rbegin = typename has_member_rbegin_impl<T>::type;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_RBEGIN_HPP
