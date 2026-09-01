/**
 *	@file	io_errc.hpp
 *
 *	@brief	io_errc の定義
 */

#ifndef HAMON_IOS_IO_ERRC_HPP
#define HAMON_IOS_IO_ERRC_HPP

#include <ios>

namespace hamon
{

using std::io_errc;

#if 0	// TODO
// [error.reporting], error reporting
enum class io_errc
{
	stream = 1
};

template<>
struct is_error_code_enum<io_errc>
	: public true_type {};
#endif

}	// namespace hamon

#endif // HAMON_IOS_IO_ERRC_HPP
