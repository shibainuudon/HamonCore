/**
 *	@file	and.hpp
 *
 *	@brief	HAMON_CONCEPTS_AND の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_AND_HPP
#define HAMON_CONCEPTS_DETAIL_AND_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)

#define HAMON_CONCEPTS_AND(C1, C2) (C1 && C2)

#else

#include <hamon/type_traits/conjunction.hpp>
#define HAMON_CONCEPTS_AND(C1, C2) hamon::conjunction<C1, C2>

#endif

#endif // HAMON_CONCEPTS_DETAIL_AND_HPP
