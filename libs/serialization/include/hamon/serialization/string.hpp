/**
 *	@file	string.hpp
 *
 *	@brief	stringのシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_STRING_HPP
#define HAMON_SERIALIZATION_STRING_HPP

#include <hamon/serialization/detail/save_string.hpp>
#include <hamon/serialization/detail/load_string.hpp>
#include <string>

namespace hamon
{

namespace serialization
{

template <typename Archive, typename CharT>
void save(Archive& oa, std::basic_string<CharT> const& t)
{
	hamon::serialization::save_string(oa, t);
}

template <typename Archive, typename CharT>
void load(Archive& ia, std::basic_string<CharT>& t)
{
	hamon::serialization::load_string(ia, t);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_STRING_HPP
