/**
 *	@file	pair.hpp
 *
 *	@brief	hamon::pair のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_PAIR_HPP
#define HAMON_SERIALIZATION_TYPES_PAIR_HPP

#include <hamon/serialization/detail/has_class_version.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/pair.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <utility>
#endif

namespace hamon
{

namespace serialization
{

template <typename Archive, typename T, typename U>
void serialize(Archive& ar, hamon::pair<T, U>& t)
{
	ar & make_nvp("first",  t.first);
	ar & make_nvp("second", t.second);
}

namespace detail
{

template <typename T, typename U>
struct has_class_version<hamon::pair<T, U>>
	: public hamon::false_type {};

}	// namespace detail

#if !defined(HAMON_NO_STD)
template <typename Archive, typename T, typename U>
void serialize(Archive& ar, std::pair<T, U>& t)
{
	ar & make_nvp("first",  t.first);
	ar & make_nvp("second", t.second);
}

namespace detail
{

template <typename T, typename U>
struct has_class_version<std::pair<T, U>>
	: public hamon::false_type {};

}	// namespace detail
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_PAIR_HPP
