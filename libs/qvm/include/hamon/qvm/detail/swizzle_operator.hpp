/**
 *	@file	swizzle_operator.hpp
 *
 *	@brief	swizzle_operator の定義
 */

#ifndef HAMON_QVM_DETAIL_SWIZZLE_OPERATOR_HPP
#define HAMON_QVM_DETAIL_SWIZZLE_OPERATOR_HPP

#include <hamon/qvm/vector/vector_fwd.hpp>
#include <hamon/preprocessor/seq/cat.hpp>
#include <hamon/preprocessor/seq/elem.hpp>
#include <hamon/preprocessor/seq/size.hpp>
#include <hamon/preprocessor/seq/for_each_product.hpp>
#include <hamon/preprocessor/punctuation/comma_if.hpp>
#include <hamon/preprocessor/repetition/repeat.hpp>
#include <hamon/config.hpp>

#define HAMON_QVM_NAMED_ACCESS(Name, I)	     \
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR    \
	T& Name(void) HAMON_NOEXCEPT             \
	{	                                     \
		return (*this)[I];	                 \
	}	                                     \
		                                     \
	HAMON_NODISCARD HAMON_CONSTEXPR          \
	T const& Name(void) const HAMON_NOEXCEPT \
	{	                                     \
		return (*this)[I];	                 \
	}

#define HAMON_QVM_SWIZZLE_ELEM(z, n, data) \
	HAMON_PP_COMMA_IF(n) this->HAMON_PP_SEQ_ELEM(n, data)()

#define HAMON_QVM_SWIZZLE_BODY(r, seq)               \
	HAMON_NODISCARD HAMON_CONSTEXPR                  \
	vector<T, HAMON_PP_SEQ_SIZE(seq)>	             \
	HAMON_PP_SEQ_CAT(seq)(void) const HAMON_NOEXCEPT \
	{	                                             \
		return {	                                 \
				HAMON_PP_REPEAT(	                 \
					HAMON_PP_SEQ_SIZE(seq),	         \
					HAMON_QVM_SWIZZLE_ELEM,	         \
					seq) };	                         \
	}

#define HAMON_QVM_SWIZZLE_OPERATOR(seq)                                         \
	HAMON_PP_SEQ_FOR_EACH_PRODUCT(HAMON_QVM_SWIZZLE_BODY, (seq)(seq)(seq)(seq)) \
	HAMON_PP_SEQ_FOR_EACH_PRODUCT(HAMON_QVM_SWIZZLE_BODY, (seq)(seq)(seq))      \
	HAMON_PP_SEQ_FOR_EACH_PRODUCT(HAMON_QVM_SWIZZLE_BODY, (seq)(seq))

#endif // HAMON_QVM_DETAIL_SWIZZLE_OPERATOR_HPP
