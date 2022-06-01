/**
 *	@file	index_sequence_for.hpp
 *
 *	@brief	index_sequence_for を定義
 */

#ifndef HAMON_UTILITY_INDEX_SEQUENCE_FOR_HPP
#define HAMON_UTILITY_INDEX_SEQUENCE_FOR_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace hamon
{

using std::index_sequence_for;

}	// namespace hamon

#else

#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// Visual Studio でのコンパイラ内部エラーを避けるため、
// いったんsizeof...(Types)を受け取る必要がある
template <typename... Types>
struct index_sequence_for_impl
{
	HAMON_STATIC_CONSTEXPR auto N = sizeof...(Types);
	using type = hamon::make_index_sequence<N>;
};

}	// namespace detail

template <typename... Types>
using index_sequence_for = typename detail::index_sequence_for_impl<Types...>::type;

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_INDEX_SEQUENCE_FOR_HPP
