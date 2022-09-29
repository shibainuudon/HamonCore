/**
 *	@file	base64.hpp
 *
 *	@brief	base64 の定義
 */

#ifndef HAMON_BASE64_BASE64_HPP
#define HAMON_BASE64_BASE64_HPP

#include <hamon/base64/detail/base64_impl.hpp>

namespace hamon
{

struct base64 : public detail::base64_impl<base64>
{
private:
	static char const* get_char_table()
	{
		return
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";
	}

	static char get_padding()
	{
		return '=';
	}

	friend struct detail::base64_impl<base64>;
};

}	// namespace hamon

#endif // HAMON_BASE64_BASE64_HPP
