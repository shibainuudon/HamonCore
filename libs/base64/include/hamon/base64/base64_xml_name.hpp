/**
 *	@file	base64_xml_name.hpp
 *
 *	@brief	base64_xml_name の定義
 */

#ifndef HAMON_BASE64_BASE64_XML_NAME_HPP
#define HAMON_BASE64_BASE64_XML_NAME_HPP

#include <hamon/base64/detail/base64_impl.hpp>

namespace hamon
{

struct base64_xml_name : public detail::base64_impl<base64_xml_name>
{
private:
	static HAMON_CONSTEXPR char const* get_char_table()
	{
		return
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789_:";
	}

	static HAMON_CONSTEXPR char get_padding()
	{
		return '\0';
	}

	friend struct detail::base64_impl<base64_xml_name>;
};

}	// namespace hamon

#endif // HAMON_BASE64_BASE64_XML_NAME_HPP
