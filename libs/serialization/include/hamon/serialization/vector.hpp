/**
 *	@file	vector.hpp
 *
 *	@brief	vectorのシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_VECTOR_HPP
#define HAMON_SERIALIZATION_VECTOR_HPP

#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/serialization/detail/load_vector.hpp>
#include <vector>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T>
void save(Archive& oa, std::vector<T> const& t)
{
	hamon::serialization::save_vector(oa, t);
}

template <typename Archive, typename T>
void load(Archive& ia, std::vector<T>& t)
{
	hamon::serialization::load_vector(ia, t);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_VECTOR_HPP
