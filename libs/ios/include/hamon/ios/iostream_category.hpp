/**
 *	@file	iostream_category.hpp
 *
 *	@brief	iostream_category の定義
 */

#ifndef HAMON_IOS_IOSTREAM_CATEGORY_HPP
#define HAMON_IOS_IOSTREAM_CATEGORY_HPP

#include <ios>

namespace hamon
{

using std::iostream_category;

#if 0	// TODO
// [error.reporting], error reporting
const error_category& iostream_category() noexcept;
#endif

}	// namespace hamon

#endif // HAMON_IOS_IOSTREAM_CATEGORY_HPP
