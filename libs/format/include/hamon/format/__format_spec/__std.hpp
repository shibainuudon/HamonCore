/**
 *	@file	__std.hpp
 *
 *	@brief	__std の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___STD_HPP
#define HAMON_FORMAT___FORMAT_SPEC___STD_HPP

#include <hamon/format/__format_spec/__alignment.hpp>
#include <hamon/format/__format_spec/__sign.hpp>
#include <hamon/format/__format_spec/__type.hpp>

namespace hamon
{

namespace __format_spec
{

struct __std
{
	__alignment __alignment_     : 3;
	__sign __sign_               : 2;
	bool __alternate_form_       : 1;
	bool __locale_specific_form_ : 1;
	__type __type_;
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___STD_HPP
