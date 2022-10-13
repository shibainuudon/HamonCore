/**
 *	@file	vector_element.hpp
 *
 *	@brief	vector_element の定義
 */

#ifndef HAMON_QVM_DETAIL_VECTOR_ELEMENT_HPP
#define HAMON_QVM_DETAIL_VECTOR_ELEMENT_HPP

#include <cstddef>
#include <array>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
struct vector_element;

template <typename T>
using vector_element_t = typename vector_element<T>::type;

template <typename T, std::size_t N>
struct vector_element<T[N]>
{
	using type = T;
};

template <typename T, std::size_t N>
struct vector_element<std::array<T, N>>
{
	using type = T;
};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_VECTOR_ELEMENT_HPP
