/**
 *	@file	__insert_sign.hpp
 *
 *	@brief	__insert_sign の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___INSERT_SIGN_HPP
#define HAMON_FORMAT___FORMATTER___INSERT_SIGN_HPP

#include <hamon/format/__format_spec/__sign.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iter_value_t.hpp>

namespace hamon
{

namespace __formatter
{

template <hamon::contiguous_iterator _Iterator>
requires hamon::same_as<char, hamon::iter_value_t<_Iterator>>
inline _Iterator __insert_sign(_Iterator __buf, bool __negative, __format_spec::__sign __sign)
{
	if (__negative)
	{
		*__buf++ = '-';
	}
	else
	{
		switch (__sign)
		{
		case __format_spec::__sign::__default:
		case __format_spec::__sign::__minus:
			// No sign added.
			break;
		case __format_spec::__sign::__plus:
			*__buf++ = '+';
			break;
		case __format_spec::__sign::__space:
			*__buf++ = ' ';
			break;
		}
	}

	return __buf;
}

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___INSERT_SIGN_HPP
