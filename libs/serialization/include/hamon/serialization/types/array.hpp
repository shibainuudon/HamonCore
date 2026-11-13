/**
 *	@file	array.hpp
 *
 *	@brief	hamon::array のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_ARRAY_HPP
#define HAMON_SERIALIZATION_TYPES_ARRAY_HPP

#include <hamon/serialization/detail/save_array.hpp>
#include <hamon/serialization/detail/load_array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <array>
#endif

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T, hamon::size_t N>
void save_value(Archive& oa, hamon::array<T, N> const& t)
{
	hamon::serialization::detail::save_array(oa, t);
}

template <typename Archive, typename T, hamon::size_t N>
void load_value(Archive& ia, hamon::array<T, N>& t)
{
	hamon::serialization::detail::load_array(ia, t);
}

#if !defined(HAMON_NO_STD)
template <typename Archive, typename T, hamon::size_t N>
void save_value(Archive& oa, std::array<T, N> const& t)
{
	hamon::serialization::detail::save_array(oa, t);
}

template <typename Archive, typename T, hamon::size_t N>
void load_value(Archive& ia, std::array<T, N>& t)
{
	hamon::serialization::detail::load_array(ia, t);
}
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_ARRAY_HPP
