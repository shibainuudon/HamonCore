/**
 *	@file	vector_rank.hpp
 *
 *	@brief	vector_rank の定義
 */

#ifndef HAMON_QVM_DETAIL_VECTOR_RANK_HPP
#define HAMON_QVM_DETAIL_VECTOR_RANK_HPP

#include <type_traits>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T>
struct vector_rank
	: public std::integral_constant<std::size_t, 0> {};

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_VECTOR_RANK_HPP
