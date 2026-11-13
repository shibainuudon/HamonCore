/**
 *	@file	string.hpp
 *
 *	@brief	hamon::string のシリアライズの定義
 */

#ifndef HAMON_SERIALIZATION_TYPES_STRING_HPP
#define HAMON_SERIALIZATION_TYPES_STRING_HPP

#include <hamon/serialization/detail/save_string.hpp>
#include <hamon/serialization/detail/load_string.hpp>
#include <hamon/string.hpp>
#include <hamon/config.hpp>

#if !defined(HAMON_NO_STD)
#include <string>
#endif

namespace hamon
{

namespace serialization
{

template <typename Archive, typename CharT>
void save_value(Archive& oa, hamon::basic_string<CharT> const& t)
{
	hamon::serialization::detail::save_string(oa, t);
}

template <typename Archive, typename CharT>
void load_value(Archive& ia, hamon::basic_string<CharT>& t)
{
	t.clear();
	hamon::serialization::detail::load_string(ia, t);
}

#if !defined(HAMON_NO_STD)
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
#endif

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_TYPES_STRING_HPP
