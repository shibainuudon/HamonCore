/**
 *	@file	tuple_size.hpp
 *
 *	@brief	tuple_size の定義
 */

#ifndef HAMON_TUPLE_TUPLE_SIZE_HPP
#define HAMON_TUPLE_TUPLE_SIZE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <tuple>

namespace hamon
{

using std::tuple_size;

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
constexpr hamon::size_t tuple_size_v = tuple_size<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_SIZE_HPP
