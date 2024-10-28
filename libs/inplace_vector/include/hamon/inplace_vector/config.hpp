/**
 *	@file	config.hpp
 *
 *	@brief
 */

#ifndef HAMON_INPLACE_VECTOR_CONFIG_HPP
#define HAMON_INPLACE_VECTOR_CONFIG_HPP

//#include <inplace_vector>

#if defined(__cpp_lib_inplace_vector) && (__cpp_lib_inplace_vector >= 202406L)

#define HAMON_USE_INPLACE_VECTOR

#endif

#endif // HAMON_INPLACE_VECTOR_CONFIG_HPP
