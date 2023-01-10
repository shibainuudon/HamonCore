/**
 *	@file	libstdcpp3.hpp
 *
 *	@brief
 */

#ifndef HAMON_CONFIG_STDLIB_LIBSTDCPP3_HPP
#define HAMON_CONFIG_STDLIB_LIBSTDCPP3_HPP

#ifdef __GLIBCXX__
#define HAMON_STDLIB "GNU libstdc++ version " HAMON_STRINGIZE(__GLIBCXX__)
#else
#define HAMON_STDLIB "GNU libstdc++ version " HAMON_STRINGIZE(__GLIBCPP__)
#endif

#define HAMON_STDLIB_LIBSTDCPP3

#endif // HAMON_CONFIG_STDLIB_LIBSTDCPP3_HPP
