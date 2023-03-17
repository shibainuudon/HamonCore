/**
 *	@file	tuple_element.hpp
 *
 *	@brief	tuple_element の定義
 */

#ifndef HAMON_TUPLE_TUPLE_ELEMENT_HPP
#define HAMON_TUPLE_TUPLE_ELEMENT_HPP

#include <hamon/cstddef/size_t.hpp>
#include <tuple>

namespace hamon
{

template <hamon::size_t I, typename T>
using tuple_element_t = typename std::tuple_element<I, T>::type;

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_ELEMENT_HPP
