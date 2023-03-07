/**
 *	@file	has_member_end.hpp
 *
 *	@brief	has_member_end の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_END_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_END_HPP

#include <hamon/ranges/begin.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_end =
	requires(T& t)
	{
		{ hamon::detail::decay_copy(t.end()) } -> hamon::sentinel_for<decltype(ranges::begin(t))>;
	};

#else

template <typename T>
struct has_member_end_impl
{
private:
	template <typename U,
		typename E = decltype(hamon::detail::decay_copy(hamon::declval<U&>().end())),
		typename B = decltype(ranges::begin(hamon::declval<U&>()))
	>
	static auto test(int) -> hamon::sentinel_for<E, B>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_end = typename has_member_end_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_END_HPP
