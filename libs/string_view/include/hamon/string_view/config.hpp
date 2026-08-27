/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_STRING_VIEW_CONFIG_HPP
#define HAMON_STRING_VIEW_CONFIG_HPP

#include <hamon/config.hpp>

#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<string_view>)
#  include <string_view>
#  define HAMON_HAS_STD_STRING_VIEW
#endif

#endif // HAMON_STRING_VIEW_CONFIG_HPP
