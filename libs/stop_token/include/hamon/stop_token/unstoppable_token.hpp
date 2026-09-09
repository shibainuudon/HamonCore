/**
 *	@file	unstoppable_token.hpp
 *
 *	@brief	unstoppable_token の定義
 */

#ifndef HAMON_STOP_TOKEN_UNSTOPPABLE_TOKEN_HPP
#define HAMON_STOP_TOKEN_UNSTOPPABLE_TOKEN_HPP

#include <hamon/stop_token/stoppable_token.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.3 Stop token concepts[stoptoken.concepts]

// [stoptoken.concepts]/4

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Token>
concept unstoppable_token =
	hamon::stoppable_token<Token> &&
	requires (Token const tok)
	{
		requires hamon::bool_constant<(!tok.stop_possible())>::value;
	};

#else

// TODO

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_UNSTOPPABLE_TOKEN_HPP
