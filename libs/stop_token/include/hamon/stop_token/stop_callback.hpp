/**
 *	@file	stop_callback.hpp
 *
 *	@brief	stop_callback の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_CALLBACK_HPP
#define HAMON_STOP_TOKEN_STOP_CALLBACK_HPP

#include <hamon/stop_token/stop_callback_fwd.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.6 Class template stop_callback[stopcallback]

template <typename CallbackFn>
class stop_callback
{
public:
	using callback_type = CallbackFn;

	// [stopcallback.cons], constructors and destructor
	template <typename Initializer>
	explicit stop_callback(hamon::stop_token const& st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>);

	template <typename Initializer>
	explicit stop_callback(hamon::stop_token&& st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>);

	~stop_callback();

	stop_callback(stop_callback const&) = delete;
	stop_callback(stop_callback&&) = delete;
	stop_callback& operator=(stop_callback const&) = delete;
	stop_callback& operator=(stop_callback&&) = delete;

private:
	CallbackFn callback_fn_;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename CallbackFn>
stop_callback(hamon::stop_token, CallbackFn) -> stop_callback<CallbackFn>;

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_CALLBACK_HPP
