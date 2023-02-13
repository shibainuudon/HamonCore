/**
 *	@file	or.hpp
 *
 *	@brief	HAMON_CONCEPTS_OR の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_OR_HPP
#define HAMON_CONCEPTS_DETAIL_OR_HPP

#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)

#define HAMON_CONCEPTS_OR(C1, C2) (C1 || C2)

#else

#include <hamon/type_traits/disjunction.hpp>
#define HAMON_CONCEPTS_OR(C1, C2) hamon::disjunction<C1, C2>

#endif

#endif // HAMON_CONCEPTS_DETAIL_OR_HPP
