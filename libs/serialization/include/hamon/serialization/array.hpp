/**
 *	@file	array.hpp
 *
 *	@brief	std::array のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_ARRAY_HPP
#define HAMON_SERIALIZATION_ARRAY_HPP

#include <hamon/serialization/detail/save_array.hpp>
#include <hamon/serialization/detail/load_array.hpp>
#include <array>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T, std::size_t N>
void save_class(Archive& oa, std::array<T, N> const& t)
{
	hamon::serialization::detail::save_array(oa, t, N);
}

template <typename Archive, typename T, std::size_t N>
void load_class(Archive& ia, std::array<T, N>& t)
{
	hamon::serialization::detail::load_array(ia, t, N);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_ARRAY_HPP
