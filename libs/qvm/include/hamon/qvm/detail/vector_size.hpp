/**
 *	@file	vector_size.hpp
 *
 *	@brief	vector_size の定義
 */

#ifndef HAMON_QVM_DETAIL_VECTOR_SIZE_HPP
#define HAMON_QVM_DETAIL_VECTOR_SIZE_HPP

#include <type_traits>
#include <cstddef>
#include <array>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
struct vector_size
	: public std::integral_constant<std::size_t, 1> {};

template <typename T, std::size_t N>
struct vector_size<T[N]>
	: public std::integral_constant<std::size_t, N> {};

template <typename T, std::size_t N>
struct vector_size<std::array<T, N>>
	: public std::integral_constant<std::size_t, N> {};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_VECTOR_SIZE_HPP
