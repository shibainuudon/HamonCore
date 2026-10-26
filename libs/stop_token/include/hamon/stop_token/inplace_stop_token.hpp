/**
 *	@file	inplace_stop_token.hpp
 *
 *	@brief	inplace_stop_token の定義
 */

#ifndef HAMON_STOP_TOKEN_INPLACE_STOP_TOKEN_HPP
#define HAMON_STOP_TOKEN_INPLACE_STOP_TOKEN_HPP

#include <hamon/stop_token/inplace_stop_token_fwd.hpp>
#include <hamon/stop_token/inplace_stop_callback_fwd.hpp>
#include <hamon/stop_token/inplace_stop_source_fwd.hpp>
#include <hamon/stop_token/detail/stop_state.hpp>
#include <hamon/utility/swap.hpp>

namespace hamon
{

// 32.3.8 Class inplace_stop_token[stoptoken.inplace]

#if 0
class inplace_stop_token
{
public:
	template <typename CallbackFn>
	using callback_type = hamon::inplace_stop_callback<CallbackFn>;

	inplace_stop_token() = default;

	bool operator==(inplace_stop_token const&) const = default;

	// [stoptoken.inplace.mem], member functions
	bool stop_requested() const noexcept
	{
		// [stoptoken.inplace.mem]/2
		return m_stop_state != nullptr && m_stop_state->stop_requested();
	}

	bool stop_possible() const noexcept
	{
		// [stoptoken.inplace.mem]/4
		return m_stop_state != nullptr;
	}

	void swap(inplace_stop_token& rhs) noexcept
	{
		// [stoptoken.inplace.mem]/1
		hamon::swap(m_stop_state, rhs.m_stop_state);
	}

private:
	explicit constexpr
	inplace_stop_token(hamon::detail::stop_state* state)
		: m_stop_state(state)
	{}

	friend class inplace_stop_source;
	template <typename>
	friend class inplace_stop_callback;

	hamon::detail::stop_state* m_stop_state = nullptr;
};
#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_INPLACE_STOP_TOKEN_HPP
