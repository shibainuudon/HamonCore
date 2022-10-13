/**
 *	@file	rebind.hpp
 *
 *	@brief	rebind の定義
 */

#ifndef HAMON_QVM_DETAIL_REBIND_HPP
#define HAMON_QVM_DETAIL_REBIND_HPP

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T, typename U>
struct rebind;

template <typename T, typename U>
using rebind_t = typename rebind<T, U>::type;

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_REBIND_HPP
