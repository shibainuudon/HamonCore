﻿/**
 *	@file	has_member_hash.hpp
 *
 *	@brief	has_member_hash
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_HAS_MEMBER_HASH_HPP
#define HAMON_FUNCTIONAL_DETAIL_HAS_MEMBER_HASH_HPP

#include <hamon/detail/decay_copy.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_hash =
	requires(T&& t)
	{
		{ decay_copy(std::forward<T>(t).hash()) } -> hamon::convertible_to<std::size_t>;
	};

#else

template <typename T>
struct has_member_hash_impl
{
private:
	template <typename U,
		typename B = decltype(decay_copy(std::declval<U&>().hash()))
	>
	static auto test(int) -> hamon::convertible_to<B, std::size_t>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_hash = typename has_member_hash_impl<T>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_HAS_MEMBER_HASH_HPP