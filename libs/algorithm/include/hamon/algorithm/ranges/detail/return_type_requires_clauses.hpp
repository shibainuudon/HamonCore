/**
 *	@file	return_type_requires_clauses.hpp
 *
 *	@brief	HAMON_RETURN_TYPE_REQUIRES_CLAUSES の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_DETAIL_RETURN_TYPE_REQUIRES_CLAUSES_HPP
#define HAMON_ALGORITHM_RANGES_DETAIL_RETURN_TYPE_REQUIRES_CLAUSES_HPP

#include <hamon/type_traits/enable_if.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> T requires __VA_ARGS__
#else
#define HAMON_RETURN_TYPE_REQUIRES_CLAUSES(T, ...)	\
	-> hamon::enable_if_t<__VA_ARGS__::value, T>
#endif

#endif // HAMON_ALGORITHM_RANGES_DETAIL_RETURN_TYPE_REQUIRES_CLAUSES_HPP
