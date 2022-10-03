/**
 *	@file	has_member_rend.hpp
 *
 *	@brief	has_member_rend の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_REND_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_REND_HPP

#include <hamon/ranges/rbegin.hpp>
#include <hamon/ranges/detail/decay_copy.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_rend =
	requires(T& t)
	{
		{ decay_copy(t.rend()) } -> hamon::sentinel_for<decltype(ranges::rbegin(t))>;
	};

#else

template <typename T>
struct has_member_rend_impl
{
private:
	template <typename U,
		typename E = decltype(decay_copy(std::declval<U&>().rend())),
		typename B = decltype(ranges::rbegin(std::declval<U&>()))
	>
	static auto test(int) -> hamon::sentinel_for<E, B>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_rend = typename has_member_rend_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_REND_HPP
