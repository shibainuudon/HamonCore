/**
 *	@file	base64url.hpp
 *
 *	@brief	base64url の定義
 */

#ifndef HAMON_BASE64_BASE64URL_HPP
#define HAMON_BASE64_BASE64URL_HPP

#include <hamon/base64/detail/base64_impl.hpp>

namespace hamon
{

struct base64url : public detail::base64_impl<base64url>
{
private:
	static char const* get_char_table()
	{
		return
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789-_";
	}

	static char get_padding()
	{
		return '\0';
	}

	friend struct detail::base64_impl<base64url>;
};

}	// namespace hamon

#endif // HAMON_BASE64_BASE64URL_HPP
