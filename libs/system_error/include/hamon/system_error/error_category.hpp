/**
 *	@file	error_category.hpp
 *
 *	@brief	error_category の定義
 */

#ifndef HAMON_SYSTEM_ERROR_ERROR_CATEGORY_HPP
#define HAMON_SYSTEM_ERROR_ERROR_CATEGORY_HPP

#include <hamon/system_error/config.hpp>

#if defined(HAMON_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace hamon
{

using std::error_category;

}	// namespace hamon

#else

namespace hamon
{

// TODO

}	// namespace hamon

#endif

#endif // HAMON_SYSTEM_ERROR_ERROR_CATEGORY_HPP
