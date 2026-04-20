/**
 *	@file	stringize.hpp
 *
 *	@brief	HAMON_STRINGIZE の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_STRINGIZE_HPP
#define HAMON_CONFIG_SUFFIX_STRINGIZE_HPP

#define HAMON_STRINGIZE(text) HAMON_STRINGIZE_I(text)
#define HAMON_STRINGIZE_I(text) #text

#endif // HAMON_CONFIG_SUFFIX_STRINGIZE_HPP
