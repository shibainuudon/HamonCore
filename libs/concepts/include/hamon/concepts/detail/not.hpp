/**
 *	@file	not.hpp
 *
 *	@brief	HAMON_CONCEPTS_NOT の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_NOT_HPP
#define HAMON_CONCEPTS_DETAIL_NOT_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)

#define HAMON_CONCEPTS_NOT(C) (!C)

#else

#include <hamon/type_traits/negation.hpp>
#define HAMON_CONCEPTS_NOT(C) hamon::negation<C>

#endif

#endif // HAMON_CONCEPTS_DETAIL_NOT_HPP
