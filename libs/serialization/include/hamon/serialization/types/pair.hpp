/**
 *	@file	pair.hpp
 *
 *	@brief	std::pair のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_PAIR_HPP
#define HAMON_SERIALIZATION_TYPES_PAIR_HPP

#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T, typename U>
void save(Archive& oa, std::pair<T, U> const& t)
{
	oa << make_nvp("first",  t.first);
	oa << make_nvp("second", t.second);
}

template <typename Archive, typename T, typename U>
void load(Archive& ia, std::pair<T, U>& t)
{
	ia >> make_nvp("first",  t.first);
	ia >> make_nvp("second", t.second);
}

namespace detail
{

template <typename T, typename U>
struct has_class_version<std::pair<T, U>>
	: public hamon::false_type {};

}	// namespace detail

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_PAIR_HPP
