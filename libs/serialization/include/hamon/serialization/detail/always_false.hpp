/**
 *	@file	always_false.hpp
 *
 *	@brief	always_falseの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_ALWAYS_FALSE_HPP
#define HAMON_SERIALIZATION_DETAIL_ALWAYS_FALSE_HPP

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename T>
struct always_false
{
	static const bool value = false;
};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_ALWAYS_FALSE_HPP
