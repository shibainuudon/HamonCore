/**
 *	@file	vector.hpp
 *
 *	@brief	hamon::vector のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_VECTOR_HPP
#define HAMON_SERIALIZATION_TYPES_VECTOR_HPP

#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/serialization/detail/load_vector.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <vector>
#endif

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T>
void save_value(Archive& oa, hamon::vector<T> const& t)
{
	hamon::serialization::detail::save_vector(oa, t);
}

template <typename Archive, typename T>
void load_value(Archive& ia, hamon::vector<T>& t)
{
	t.clear();
	hamon::serialization::detail::load_vector(ia, t);
}

#if !defined(HAMON_NO_STD)
template <typename Archive, typename T>
void save_value(Archive& oa, std::vector<T> const& t)
{
	hamon::serialization::detail::save_vector(oa, t);
}

template <typename Archive, typename T>
void load_value(Archive& ia, std::vector<T>& t)
{
	t.clear();
	hamon::serialization::detail::load_vector(ia, t);
}
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_VECTOR_HPP
