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
#include <hamon/type_traits/bool_constant.hpp>
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
HAMON_CONCEPT_OR_BOOL stoppable_token =
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

template <typename Token>
struct stoppable_token_impl
{
private:
	template <typename Token2,
		typename = typename detail::check_type_alias_exists<Token2::template callback_type>,
		typename R1 = decltype(hamon::declval<Token2 const&>().stop_requested()),
		typename = hamon::enable_if_t<hamon::same_as<R1, bool>>,
		typename = hamon::enable_if_t<noexcept(hamon::declval<Token2 const&>().stop_requested())>,
		typename R2 = decltype(hamon::declval<Token2 const&>().stop_possible()),
		typename = hamon::enable_if_t<hamon::same_as<R2, bool>>,
		typename = hamon::enable_if_t<noexcept(hamon::declval<Token2 const&>().stop_possible())>,
		typename = hamon::enable_if_t<noexcept(Token2(hamon::declval<Token2 const&>()))>,
		typename = hamon::enable_if_t<hamon::copyable<Token2>>,
		typename = hamon::enable_if_t<hamon::equality_comparable<Token2>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename Token2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Token>(0));
};

template <typename Token>
HAMON_CONCEPT_OR_BOOL stoppable_token =
	stoppable_token_impl<Token>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOPPABLE_TOKEN_HPP
