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
#include <hamon/concepts/destructible.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/enable_if.hpp>
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
private:
	// [stopcallback.general]/2
	static_assert(hamon::invocable<CallbackFn>, "");
	static_assert(hamon::destructible<CallbackFn>, "");

public:
	using callback_type = CallbackFn;

	// [stopcallback.cons], constructors and destructor
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename Initializer>
		// [stopcallback.cons]/1
		requires hamon::constructible_from<CallbackFn, Initializer>
#else
	template <typename Initializer,
		typename = hamon::enable_if_t<hamon::constructible_from<CallbackFn, Initializer>>>
#endif
	explicit stop_callback(hamon::stop_token const& st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>)
		: stop_callback_base(
			[](stop_callback_base* cb_base) noexcept
			{
				// stop callback is supposed to only be called once
				hamon::forward<CallbackFn>(static_cast<stop_callback*>(cb_base)->m_callback_fn)();
			})
		, m_callback_fn(hamon::forward<Initializer>(init))	// [stopcallback.cons]/2
	{
		if (st.m_stop_state && st.m_stop_state->add_callback(this))
		{
			// st.stop_requested() was false and this is successfully added to the linked list
			m_stop_state = st.m_stop_state;
		}
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	template <typename Initializer>
		// [stopcallback.cons]/1
		requires hamon::constructible_from<CallbackFn, Initializer>
#else
	template <typename Initializer,
		typename = hamon::enable_if_t<hamon::constructible_from<CallbackFn, Initializer>>>
#endif
	explicit stop_callback(hamon::stop_token&& st, Initializer&& init)
		noexcept(hamon::is_nothrow_constructible_v<CallbackFn, Initializer>)
		: stop_callback_base(
			[](stop_callback_base* cb_base) noexcept
			{
				// stop callback is supposed to only be called once
				hamon::forward<CallbackFn>(static_cast<stop_callback*>(cb_base)->m_callback_fn)();
			})
		, m_callback_fn(hamon::forward<Initializer>(init))	// [stopcallback.cons]/2
	{
		if (st.m_stop_state && st.m_stop_state->add_callback(this))
		{
			// st.stop_requested() was false and this is successfully added to the linked list
			m_stop_state = hamon::move(st.m_stop_state);
		}
	}

	~stop_callback()
	{
		if (m_stop_state)
		{
			m_stop_state->remove_callback(this);
		}
	}

	stop_callback(stop_callback const&)            = delete;
	stop_callback(stop_callback&&)                 = delete;
	stop_callback& operator=(stop_callback const&) = delete;
	stop_callback& operator=(stop_callback&&)      = delete;

private:
	HAMON_NO_UNIQUE_ADDRESS CallbackFn m_callback_fn;
	hamon::shared_ptr<hamon::detail::stop_state> m_stop_state;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename CallbackFn>
stop_callback(hamon::stop_token, CallbackFn) -> stop_callback<CallbackFn>;

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_STOP_CALLBACK_HPP
