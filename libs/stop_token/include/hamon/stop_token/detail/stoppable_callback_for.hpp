/**
 *	@file	stoppable_callback_for.hpp
 *
 *	@brief	stoppable_callback_for の定義
 */

#ifndef HAMON_STOP_TOKEN_DETAIL_STOPPABLE_CALLBACK_FOR_HPP
#define HAMON_STOP_TOKEN_DETAIL_STOPPABLE_CALLBACK_FOR_HPP

#include <hamon/stop_token/stop_callback_for_t.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

// 32.3.3 Stop token concepts[stoptoken.concepts]

// [stoptoken.concepts]/1

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename CallbackFn, typename Token, typename Initializer = CallbackFn>
concept stoppable_callback_for =
	hamon::invocable<CallbackFn> &&
	hamon::constructible_from<CallbackFn, Initializer> &&
	requires { typename hamon::stop_callback_for_t<Token, CallbackFn>; } &&
	hamon::constructible_from<hamon::stop_callback_for_t<Token, CallbackFn>, Token const&, Initializer>;

#else

// TODO

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_STOP_TOKEN_DETAIL_STOPPABLE_CALLBACK_FOR_HPP
