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

#if 0
template <typename CallbackFn>
class inplace_stop_callback : private hamon::detail::stop_callback_base
{
public:
	using callback_type = CallbackFn;

	// [stopcallback.inplace.cons], constructors and destructor
	template <typename Initializer>
		// [stopcallback.inplace.cons]/1
		requires hamon::constructible_from<CallbackFn, Initializer>
	explicit inplace_stop_callback(hamon::inplace_stop_token st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>)
		: stop_callback_base(
			[](stop_callback_base* cb_base) noexcept
			{
				// stop callback is supposed to only be called once
				hamon::forward<CallbackFn>(static_cast<inplace_stop_callback*>(cb_base)->m_callback_fn)();
			})
		, m_callback_fn(hamon::forward<Initializer>(init))	// [stopcallback.cons]/2
	{
		if (st.m_stop_state && st.m_stop_state->add_callback(this))
		{
			// st.stop_requested() was false and this is successfully added to the linked list
			m_stop_state = st.m_stop_state;
		}
	}

	~inplace_stop_callback()
	{
		if (m_stop_state)
		{
			m_stop_state->remove_callback(this);
		}
	}

	inplace_stop_callback(inplace_stop_callback&&) = delete;
	inplace_stop_callback(inplace_stop_callback const&) = delete;
	inplace_stop_callback& operator=(inplace_stop_callback&&) = delete;
	inplace_stop_callback& operator=(inplace_stop_callback const&) = delete;

private:
	CallbackFn m_callback_fn;
	hamon::detail::stop_state* m_stop_state = nullptr;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename CallbackFn>
inplace_stop_callback(hamon::inplace_stop_token, CallbackFn)
-> inplace_stop_callback<CallbackFn>;

#endif
#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_INPLACE_STOP_CALLBACK_HPP
