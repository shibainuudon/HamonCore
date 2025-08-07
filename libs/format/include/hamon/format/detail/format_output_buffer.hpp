/**
 *	@file	format_output_buffer.hpp
 *
 *	@brief	format_output_buffer の定義
 */

#ifndef HAMON_FORMAT_DETAIL_FORMAT_OUTPUT_BUFFER_HPP
#define HAMON_FORMAT_DETAIL_FORMAT_OUTPUT_BUFFER_HPP

#include <hamon/string.hpp>

namespace hamon
{

namespace detail
{

//template <typename charT>
//class format_output_buffer
//{
//};

template <typename charT>
using format_output_buffer = hamon::basic_string<charT>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FORMAT_DETAIL_FORMAT_OUTPUT_BUFFER_HPP
