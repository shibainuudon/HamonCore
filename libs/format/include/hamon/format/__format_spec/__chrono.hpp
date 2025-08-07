/**
 *	@file	__chrono.hpp
 *
 *	@brief	__chrono の定義
 */

#ifndef HAMON_FORMAT___FORMAT_SPEC___CHRONO_HPP
#define HAMON_FORMAT___FORMAT_SPEC___CHRONO_HPP

#include <hamon/format/__format_spec/__alignment.hpp>

namespace hamon
{

namespace __format_spec
{

struct __chrono
{
	__alignment __alignment_     : 3;
	bool __locale_specific_form_ : 1;
	bool __hour_                 : 1;
	bool __weekday_name_         : 1;
	bool __weekday_              : 1;
	bool __day_of_year_          : 1;
	bool __week_of_year_         : 1;
	bool __month_name_           : 1;
};

}	// namespace __format_spec

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT_SPEC___CHRONO_HPP
