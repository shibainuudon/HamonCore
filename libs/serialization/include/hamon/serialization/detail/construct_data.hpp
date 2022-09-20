/**
 *	@file	construct_data.hpp
 *
 *	@brief	construct_dataの定義
 */

#ifndef HAMON_SERIALIZATION_DETAIL_CONSTRUCT_DATA_HPP
#define HAMON_SERIALIZATION_DETAIL_CONSTRUCT_DATA_HPP

#include <hamon/serialization/detail/save_construct_data.hpp>
#include <hamon/serialization/detail/load_construct_data.hpp>

namespace hamon
{

namespace serialization
{

namespace detail
{

template <typename T>
struct construct_data
{
	T*	m_p;
};

}	// namespace detail

template <typename Archive, typename T>
void save_value(Archive& oa, detail::construct_data<T> const& t)
{
	hamon::serialization::detail::save_construct_data(oa, t.m_p);
}

template <typename Archive, typename T>
void load_value(Archive& ia, detail::construct_data<T>& t)
{
	hamon::serialization::detail::load_construct_data(ia, t.m_p);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_DETAIL_CONSTRUCT_DATA_HPP
