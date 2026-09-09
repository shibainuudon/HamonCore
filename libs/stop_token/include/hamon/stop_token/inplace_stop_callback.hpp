/**
 *	@file	inplace_stop_callback.hpp
 *
 *	@brief	inplace_stop_callback の定義
 */

#ifndef HAMON_STOP_TOKEN_INPLACE_STOP_CALLBACK_HPP
#define HAMON_STOP_TOKEN_INPLACE_STOP_CALLBACK_HPP

#include <hamon/stop_token/inplace_stop_callback_fwd.hpp>
#include <hamon/stop_token/inplace_stop_token.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.10 Class template inplace_stop_callback[stopcallback.inplace]

template <typename CallbackFn>
class inplace_stop_callback
{
public:
	using callback_type = CallbackFn;

	// [stopcallback.inplace.cons], constructors and destructor
	template <typename Initializer>
	explicit inplace_stop_callback(hamon::inplace_stop_token st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>);

	~inplace_stop_callback();

	inplace_stop_callback(inplace_stop_callback&&) = delete;
	inplace_stop_callback(inplace_stop_callback const&) = delete;
	inplace_stop_callback& operator=(inplace_stop_callback&&) = delete;
	inplace_stop_callback& operator=(inplace_stop_callback const&) = delete;

private:
	CallbackFn callback_fn_;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename CallbackFn>
inplace_stop_callback(hamon::inplace_stop_token, CallbackFn)
-> inplace_stop_callback<CallbackFn>;

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_INPLACE_STOP_CALLBACK_HPP
