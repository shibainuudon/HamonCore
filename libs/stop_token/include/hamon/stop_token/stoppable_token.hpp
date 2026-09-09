/**
 *	@file	stoppable_token.hpp
 *
 *	@brief	stoppable_token の定義
 */

#ifndef HAMON_STOP_TOKEN_STOPPABLE_TOKEN_HPP
#define HAMON_STOP_TOKEN_STOPPABLE_TOKEN_HPP

#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.3 Stop token concepts[stoptoken.concepts]

// [stoptoken.concepts]/4

namespace detail
{

template <template<typename> class>
struct check_type_alias_exists;

}	// namespace detail

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Token>
concept stoppable_token =
	requires (Token const tok)
	{
		typename detail::check_type_alias_exists<Token::template callback_type>;
		{ tok.stop_requested() } noexcept -> hamon::same_as<bool>;
		{ tok.stop_possible() } noexcept -> hamon::same_as<bool>;
		{ Token(tok) } noexcept;                  // see implicit expression variations ([concepts.equality])
	} &&
	hamon::copyable<Token> &&
	hamon::equality_comparable<Token>;

#else

// TODO

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOPPABLE_TOKEN_HPP
