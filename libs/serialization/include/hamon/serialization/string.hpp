/**
 *	@file	string.hpp
 *
 *	@brief	std::string のシリアライズの定義
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
void save_value(Archive& oa, std::basic_string<CharT> const& t)
{
	hamon::serialization::detail::save_string(oa, t);
}

template <typename Archive, typename CharT>
void load_value(Archive& ia, std::basic_string<CharT>& t)
{
	t.clear();
	hamon::serialization::detail::load_string(ia, t);
}

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_STRING_HPP
