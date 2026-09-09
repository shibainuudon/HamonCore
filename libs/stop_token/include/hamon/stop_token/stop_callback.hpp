/**
 *	@file	stop_callback.hpp
 *
 *	@brief	stop_callback の定義
 */

#ifndef HAMON_STOP_TOKEN_STOP_CALLBACK_HPP
#define HAMON_STOP_TOKEN_STOP_CALLBACK_HPP

#include <hamon/stop_token/stop_callback_fwd.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/detail/stop_callback_base.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.6 Class template stop_callback[stopcallback]

template <typename CallbackFn>
class stop_callback : private hamon::detail::stop_callback_base
{
public:
	using callback_type = CallbackFn;

	// [stopcallback.cons], constructors and destructor
	template <typename Initializer>
		// [stopcallback.cons]/1
		requires hamon::constructible_from<CallbackFn, Initializer>
	explicit stop_callback(hamon::stop_token const& st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>)
		: stop_callback_base(
			[](stop_callback_base* __cb_base) noexcept
			{
				// stop callback is supposed to only be called once
				hamon::forward<CallbackFn>(static_cast<stop_callback*>(__cb_base)->callback_fn_)();
			})
		, callback_fn_(hamon::forward<Initializer>(init))	// [stopcallback.cons]/2
	{
		if (st && st->__add_callback(this))
		{
			// st.stop_requested() was false and this is successfully added to the linked list
			stop_state_ = st;
		}
	}

	template <typename Initializer>
		// [stopcallback.cons]/1
		requires hamon::constructible_from<CallbackFn, Initializer>
	explicit stop_callback(hamon::stop_token&& st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>)
		: stop_callback_base(
			[](stop_callback_base* __cb_base) noexcept
			{
				// stop callback is supposed to only be called once
				hamon::forward<CallbackFn>(static_cast<stop_callback*>(__cb_base)->callback_fn_)();
			})
		, callback_fn_(hamon::forward<Initializer>(init))	// [stopcallback.cons]/2
	{
		if (st && st->__add_callback(this))
		{
			// st.stop_requested() was false and this is successfully added to the linked list
			stop_state_ = hamon::move(st);
		}
	}

	~stop_callback();

	stop_callback(stop_callback const&) = delete;
	stop_callback(stop_callback&&) = delete;
	stop_callback& operator=(stop_callback const&) = delete;
	stop_callback& operator=(stop_callback&&) = delete;

private:
	CallbackFn callback_fn_;
	hamon::shared_ptr<hamon::detail::stop_state> stop_state_;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename CallbackFn>
stop_callback(hamon::stop_token, CallbackFn) -> stop_callback<CallbackFn>;

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_CALLBACK_HPP
