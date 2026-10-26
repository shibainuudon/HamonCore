/**
 *	@file	unit_test_stop_token_unstoppable_token.cpp
 *
 *	@brief	unstoppable_token のテスト
 *
 *	template<class Token>
 *	concept unstoppable_token =
 *		stoppable_token<Token> &&
 *		requires (const Token tok) {
 *			requires bool_constant<(!tok.stop_possible())>::value;
 *		};
 */

#include <hamon/stop_token/unstoppable_token.hpp>

namespace hamon_stop_token_test
{

namespace unstoppable_token_test
{

struct StopToken1
{
	template <typename>
	using callback_type = void;

	bool stop_requested() const noexcept;
	constexpr bool stop_possible() const noexcept { return false; }
	bool operator==(StopToken1 const& rhs) const noexcept;
	bool operator!=(StopToken1 const& rhs) const noexcept;
};

struct StopToken2
{
	template <typename>
	using callback_type = void;

	bool stop_requested() const noexcept;
	/*constexpr*/ bool stop_possible() const noexcept { return false; }
	bool operator==(StopToken2 const& rhs) const noexcept;
	bool operator!=(StopToken2 const& rhs) const noexcept;
};

struct StopToken3
{
	template <typename>
	using callback_type = void;

	bool stop_requested() const noexcept;
	constexpr bool stop_possible() const noexcept { return /*false*/true; }
	bool operator==(StopToken3 const& rhs) const noexcept;
	bool operator!=(StopToken3 const& rhs) const noexcept;
};

static_assert( hamon::unstoppable_token<StopToken1>, "");
static_assert(!hamon::unstoppable_token<StopToken2>, "");
static_assert(!hamon::unstoppable_token<StopToken3>, "");

}	// namespace unstoppable_token_test

}	// namespace hamon_stop_token_test
