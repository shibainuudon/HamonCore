/**
 *	@file	unit_test_stop_token_stoppable_token.cpp
 *
 *	@brief	stoppable_token のテスト
 *
 *	template<template<class> class>
 *	struct check-type-alias-exists;                               // exposition only
 *
 *	template<class Token>
 *	concept stoppable_token =
 *	requires (const Token tok) {
 *		typename check-type-alias-exists<Token::template callback_type>;
 *		{ tok.stop_requested() } noexcept -> same_as<bool>;
 *		{ tok.stop_possible() } noexcept -> same_as<bool>;
 *		{ Token(tok) } noexcept;                  // see implicit expression variations ([concepts.equality])
 *	} &&
 *	copyable<Token> &&
 *	equality_comparable<Token>;
 */

#include <hamon/stop_token/stoppable_token.hpp>

namespace hamon_stop_token_test
{

namespace stoppable_token_test
{

struct StopToken1
{
	template <typename>
	using callback_type = void;

	StopToken1(StopToken1 const&) noexcept;

	bool stop_requested() const noexcept;
	bool stop_possible() const noexcept;
	bool operator==(StopToken1 const& rhs) const noexcept;
	bool operator!=(StopToken1 const& rhs) const noexcept;
};

struct StopToken2
{
	//template <typename>
	//using callback_type = void;

	StopToken2(StopToken2 const&) noexcept;

	bool stop_requested() const noexcept;
	bool stop_possible() const noexcept;
	bool operator==(StopToken2 const& rhs) const noexcept;
	bool operator!=(StopToken2 const& rhs) const noexcept;
};

struct StopToken3
{
	template <typename>
	using callback_type = void;

	StopToken3(StopToken3 const&) noexcept;

	/*bool*/int stop_requested() const noexcept;
	bool stop_possible() const noexcept;
	bool operator==(StopToken3 const& rhs) const noexcept;
	bool operator!=(StopToken3 const& rhs) const noexcept;
};

struct StopToken4
{
	template <typename>
	using callback_type = void;

	StopToken4(StopToken4 const&) noexcept;

	bool stop_requested() /*const*/ noexcept;
	bool stop_possible() const noexcept;
	bool operator==(StopToken4 const& rhs) const noexcept;
	bool operator!=(StopToken4 const& rhs) const noexcept;
};

struct StopToken5
{
	template <typename>
	using callback_type = void;

	StopToken5(StopToken5 const&) noexcept;

	bool stop_requested() const /*noexcept*/;
	bool stop_possible() const noexcept;
	bool operator==(StopToken5 const& rhs) const noexcept;
	bool operator!=(StopToken5 const& rhs) const noexcept;
};

struct StopToken6
{
	template <typename>
	using callback_type = void;

	StopToken6(StopToken6 const&) noexcept;

	bool stop_requested() const noexcept;
	/*bool*/int stop_possible() const noexcept;
	bool operator==(StopToken6 const& rhs) const noexcept;
	bool operator!=(StopToken6 const& rhs) const noexcept;
};

struct StopToken7
{
	template <typename>
	using callback_type = void;

	StopToken7(StopToken7 const&) noexcept;

	bool stop_requested() const noexcept;
	bool stop_possible() /*const*/ noexcept;
	bool operator==(StopToken7 const& rhs) const noexcept;
	bool operator!=(StopToken7 const& rhs) const noexcept;
};

struct StopToken8
{
	template <typename>
	using callback_type = void;

	StopToken8(StopToken8 const&) noexcept;

	bool stop_requested() const noexcept;
	bool stop_possible() const /*noexcept*/;
	bool operator==(StopToken8 const& rhs) const noexcept;
	bool operator!=(StopToken8 const& rhs) const noexcept;
};

struct StopToken9
{
	template <typename>
	using callback_type = void;

	StopToken9(StopToken9 const&) /*noexcept*/;

	bool stop_requested() const noexcept;
	bool stop_possible() const noexcept;
	bool operator==(StopToken9 const& rhs) const noexcept;
	bool operator!=(StopToken9 const& rhs) const noexcept;
};

struct StopToken10
{
	template <typename>
	using callback_type = void;

	StopToken10(StopToken10 const&) noexcept;

	bool stop_requested() const noexcept;
	bool stop_possible() const noexcept;
	//bool operator==(StopToken10 const& rhs) const noexcept;
	//bool operator!=(StopToken10 const& rhs) const noexcept;
};

static_assert( hamon::stoppable_token<StopToken1>, "");
static_assert(!hamon::stoppable_token<StopToken2>, "");
static_assert(!hamon::stoppable_token<StopToken3>, "");
static_assert(!hamon::stoppable_token<StopToken4>, "");
static_assert(!hamon::stoppable_token<StopToken5>, "");
static_assert(!hamon::stoppable_token<StopToken6>, "");
static_assert(!hamon::stoppable_token<StopToken7>, "");
static_assert(!hamon::stoppable_token<StopToken8>, "");
static_assert(!hamon::stoppable_token<StopToken9>, "");
static_assert(!hamon::stoppable_token<StopToken10>, "");

}	// namespace stoppable_token_test

}	// namespace hamon_stop_token_test
