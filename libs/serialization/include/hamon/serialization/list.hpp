/**
 *	@file	list.hpp
 *
 *	@brief	listのシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_LIST_HPP
#define HAMON_SERIALIZATION_LIST_HPP

#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/serialization/detail/load_vector.hpp>
#include <list>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T>
void save_value(Archive& oa, std::list<T> const& t)
{
	hamon::serialization::detail::save_vector(oa, t);
}

template <typename Archive, typename T>
void load_value(Archive& ia, std::list<T>& t)
{
	t.clear();
	hamon::serialization::detail::load_vector(ia, t);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_LIST_HPP
