/**
 *	@file	make_integer_sequence.hpp
 *
 *	@brief	make_integer_sequence を定義
 */

#ifndef HAMON_UTILITY_MAKE_INTEGER_SEQUENCE_HPP
#define HAMON_UTILITY_MAKE_INTEGER_SEQUENCE_HPP

#include <hamon/utility/integer_sequence.hpp>
#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace hamon
{

using std::make_integer_sequence;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{

namespace detail
{

/*=============================================================================
この実装はボレロ村上氏による、再帰深度をO(logN)に抑える実装をもとにしています。

http://boleros.hateblo.jp/entry/20130127/1359292468
https://groups.google.com/a/isocpp.org/forum/#!topic/std-proposals/SewNyDdXXGI

Copyright (c) 2011-2015 Bolero MURAKAMI
=============================================================================*/

template <typename T, typename Seq, T Next>
struct make_integer_sequence_next_even;

template <typename T, T... I, T Next>
struct make_integer_sequence_next_even<T, hamon::integer_sequence<T, I...>, Next>
{
	using type = hamon::integer_sequence<T, I..., (I + Next)...>;
};

template <typename T, typename Seq, T Next, T Last>
struct make_integer_sequence_next_odd;

template <typename T, T... I, T Next, T Last>
struct make_integer_sequence_next_odd<T, hamon::integer_sequence<T, I...>, Next, Last>
{
	using type = hamon::integer_sequence<T, I..., (I + Next)..., Last>;
};

template <typename T, T N, typename Enable = void>
struct make_integer_sequence_impl;

template <typename T, T N>
using make_integer_sequence_impl_t = typename make_integer_sequence_impl<T, N>::type;

template <typename T, T N>
struct make_integer_sequence_impl<T, N, hamon::enable_if_t<(N == 0)>>
{
	using type = hamon::integer_sequence<T>;
};

template <typename T, T N>
struct make_integer_sequence_impl<T, N, hamon::enable_if_t<(N == 1)>>
{
	using type = hamon::integer_sequence<T, 0>;
};

template <typename T, T N>
struct make_integer_sequence_impl<T, N, hamon::enable_if_t<(N > 1 && N % 2 == 0)>>
	: public make_integer_sequence_next_even<T, make_integer_sequence_impl_t<T, N / 2>, N / 2>
{
};

template <typename T, T N>
struct make_integer_sequence_impl<T, N, hamon::enable_if_t<(N > 1 && N % 2 == 1)>>
	: public make_integer_sequence_next_odd<T, make_integer_sequence_impl_t<T, N / 2>, N / 2, N - 1>
{
};

}	// namespace detail

template <typename T, T N>
using make_integer_sequence = typename hamon::detail::make_integer_sequence_impl<T, N>::type;

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_MAKE_INTEGER_SEQUENCE_HPP
