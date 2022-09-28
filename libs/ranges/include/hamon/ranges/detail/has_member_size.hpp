﻿/**
 *	@file	has_member_size.hpp
 *
 *	@brief	has_member_size の定義
 */

#ifndef HAMON_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP
#define HAMON_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP

#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/ranges/detail/decay_copy.hpp>
#include <hamon/ranges/detail/integer_like.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
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
concept has_member_size =
	!HAMON_RANGES_DISABLE_SIZED_RANGE(hamon::remove_cvref_t<T>) &&
	requires(T&& t)
	{
		{ decay_copy(std::forward<T>(t).size()) } -> detail::integer_like;
	};

#else

template <typename T>
struct has_member_size_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			!HAMON_RANGES_DISABLE_SIZED_RANGE(hamon::remove_cvref_t<U>)
		>,
		typename S = decltype(decay_copy(std::declval<U&&>().size()))
	>
	static auto test(int) -> detail::integer_like<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_size = typename has_member_size_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_HAS_MEMBER_SIZE_HPP