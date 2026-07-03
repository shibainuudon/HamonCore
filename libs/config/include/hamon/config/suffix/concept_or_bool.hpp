/**
 *	@file	concept_or_bool.hpp
 *
 *	@brief	HAMON_CONCEPT_OR_BOOL の定義
 */

#ifndef HAMON_CONFIG_SUFFIX_CONCEPT_OR_BOOL_HPP
#define HAMON_CONFIG_SUFFIX_CONCEPT_OR_BOOL_HPP

#include <hamon/config/suffix/inline_var.hpp>

#if !defined(HAMON_CONCEPT_OR_BOOL)
#	if defined(HAMON_HAS_CXX20_CONCEPTS)
#		define HAMON_CONCEPT_OR_BOOL concept
#	else
#		define HAMON_CONCEPT_OR_BOOL HAMON_INLINE_VAR constexpr bool
#	endif
#endif

#endif // HAMON_CONFIG_SUFFIX_CONCEPT_OR_BOOL_HPP
