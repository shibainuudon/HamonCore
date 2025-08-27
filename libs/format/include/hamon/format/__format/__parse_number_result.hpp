/**
 *	@file	__parse_number_result.hpp
 *
 *	@brief	__parse_number_result の定義
 */

#ifndef HAMON_FORMAT___FORMAT___PARSE_NUMBER_RESULT_HPP
#define HAMON_FORMAT___FORMAT___PARSE_NUMBER_RESULT_HPP


namespace hamon
{

namespace __format
{

template <contiguous_iterator _Iterator>
struct __parse_number_result
{
	_Iterator __last;
	uint32_t __value;
};

template <contiguous_iterator _Iterator>
__parse_number_result(_Iterator, uint32_t)->__parse_number_result<_Iterator>;

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___PARSE_NUMBER_RESULT_HPP
